open BsReactNative;

module type NavigationConfig = {type route;};

module StringMap =
  Map.Make(
    {
      type t = string;
      let compare = compare;
    }
  );

module CreateNavigation = (Config: NavigationConfig) => {
  module StackNavigator = {
    type headerConfig = {title: option(string)};
    type screenKey = string;
    type screenConfig = {
      route: Config.route,
      index: int,
      key: screenKey
    };
    type state = {
      screens: list(screenConfig),
      headers: StringMap.t(headerConfig),
      activeScene: int,
      visibleScene: Animated.Value.t
    };
    type action =
      | Push(Config.route)
      | SetHeaderOptions(screenKey, headerConfig)
      | RemoveStaleScenes
      | Pop;
    type navigation = {
      send: action => unit,
      key: screenKey
    };
    module Header = {
      let component = ReasonReact.statelessComponent("StackHeader");
      let def = (opt, def) =>
        switch opt {
        | Some(value) => value
        | None => def
        };
      let make = (~config: headerConfig, _children) => {
        ...component,
        render: _self =>
          <View>
            <Text> (ReasonReact.stringToElement(def(config.title, ""))) </Text>
          </View>
      };
    };
    module Styles = {
      let card =
        Style.(
          style([
            position(Absolute),
            top(Pt(0.0)),
            left(Pt(0.0)),
            right(Pt(0.0)),
            bottom(Pt(0.0)),
            backgroundColor("#ffffff")
          ])
        );
    };
    let component = ReasonReact.reducerComponent("StackNavigator");
    let make = (~initialRoute, children) => {
      ...component,
      initialState: () => {
        screens: [{route: initialRoute, index: 0, key: "0"}],
        headers: StringMap.empty,
        activeScene: 0,
        visibleScene: Animated.Value.create(0.0)
      },
      didUpdate: ({oldSelf, newSelf: self}) =>
        if (oldSelf.state.activeScene != self.state.activeScene) {
          Animated.(
            CompositeAnimation.start(
              Timing.animate(
                ~value=self.state.visibleScene,
                ~duration=300.0,
                ~toValue=`raw(float_of_int(self.state.activeScene)),
                ()
              ),
              ~callback=_end => self.send(RemoveStaleScenes),
              ()
            )
          );
        },
      reducer: (action, state) =>
        switch action {
        | Push(route) =>
          let index = List.length(state.screens);
          let screen = {route, index, key: string_of_int(index)};
          ReasonReact.Update({
            ...state,
            activeScene: index,
            screens: [screen, ...state.screens]
          });
        | Pop =>
          List.length(state.screens) > 1 ?
            ReasonReact.Update({
              ...state,
              activeScene: state.activeScene - 1
            }) :
            ReasonReact.NoUpdate
        | RemoveStaleScenes =>
          ReasonReact.Update({
            ...state,
            screens:
              Utils.dropWhile(
                el => el.index > state.activeScene,
                state.screens
              )
          })
        | SetHeaderOptions(screenKey, options) =>
          ReasonReact.Update({
            ...state,
            headers: StringMap.add(screenKey, options, state.headers)
          })
        },
      render: self =>
        self.state.screens
        |> List.rev_map((screen: screenConfig) => {
             let width = float(Dimensions.get(`window)##width);
             let transform =
               Style.Transform.makeInterpolated(
                 ~translateX=
                   Animated.Value.interpolate(
                     self.state.visibleScene,
                     ~inputRange=
                       [screen.index - 1, screen.index, screen.index + 1]
                       |> List.map(float),
                     ~outputRange=`float([-. width, 0.0, width *. 0.3]),
                     ()
                   ),
                 ()
               );
             <Animated.View
               key=screen.key
               style=Style.(concat([Styles.card, style([transform])]))>
               (
                 switch (StringMap.find(screen.key, self.state.headers)) {
                 | config => <Header config />
                 | exception Not_found => <View />
                 }
               )
               <View style=Style.(style([flex(1.0)]))>
                 (
                   children(
                     ~currentRoute=screen.route,
                     ~navigation={send: self.send, key: screen.key}
                   )
                 )
               </View>
             </Animated.View>;
           })
        |> Array.of_list
        |> ReasonReact.arrayToElement
    };
  };
  module Screen = {
    open StackNavigator;
    let component = ReasonReact.statelessComponent("CallstackScreen");
    let make = (~navigation: navigation, ~headerTitle=?, children) => {
      ...component,
      didMount: _self => {
        navigation.send(
          SetHeaderOptions(navigation.key, {title: headerTitle})
        );
        ReasonReact.NoUpdate;
      },
      render: _self => {
        let body = children();
        <View> body </View>;
      }
    };
  };
};
