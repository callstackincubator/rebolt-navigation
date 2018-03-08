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
      key: screenKey
    };
    type state = {
      screens: list(screenConfig),
      headers: StringMap.t(headerConfig),
      activeScene: Animated.Value.t
    };
    type action =
      | Push(Config.route)
      | SetHeaderOptions(screenKey, headerConfig)
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
        screens: [{route: initialRoute, key: "0"}],
        headers: StringMap.empty,
        activeScene: Animated.Value.create(0.0)
      },
      didUpdate: ({oldSelf, newSelf}) =>
        if (oldSelf.state.screens != newSelf.state.screens) {
          Animated.(
            CompositeAnimation.start(
              Timing.animate(
                ~value=newSelf.state.activeScene,
                ~duration=300.0,
                ~toValue=
                  `raw(float_of_int(List.length(newSelf.state.screens))),
                ()
              ),
              ()
            )
          );
        },
      reducer: (action, state) =>
        switch action {
        | Push(route) =>
          let screen = {route, key: string_of_int(List.length(state.screens))};
          ReasonReact.Update({...state, screens: [screen, ...state.screens]});
        | Pop =>
          List.(
            length(state.screens) > 1 ?
              ReasonReact.Update({...state, screens: tl(state.screens)}) :
              ReasonReact.NoUpdate
          )
        | SetHeaderOptions(screenKey, options) =>
          ReasonReact.Update({
            ...state,
            headers: StringMap.add(screenKey, options, state.headers)
          })
        },
      render: self =>
        self.state.screens
        |> List.rev_map((screen: screenConfig) => {
             let transform =
               Style.Transform.makeInterpolated(
                 ~translateX=
                   Animated.Value.interpolate(
                     self.state.activeScene,
                     ~inputRange=[0.0, 1.0],
                     ~outputRange=`float([0.0, 1.0]),
                     ()
                   ),
                 ()
               );
             <View
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
             </View>;
           })
        |> Array.of_list
        |> ReasonReact.arrayToElement
    };
  };
  module Header = {
    open StackNavigator;
    let component = ReasonReact.statelessComponent("CallstackHeader");
    let make = (~navigation: navigation, ~title=?, _children) => {
      ...component,
      didMount: _self => {
        navigation.send(SetHeaderOptions(navigation.key, {title: title}));
        ReasonReact.NoUpdate;
      },
      render: _self => <View />
    };
  };
};
