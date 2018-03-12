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
    type screenConfig = {
      route: Config.route,
      key: string,
      header: option(headerConfig)
    };
    type state = {
      screens: array(screenConfig),
      activeScene: int,
      visibleScene: Animated.Value.t
    };
    type action =
      | Push(Config.route)
      | SetHeaderOptions(int, headerConfig)
      | RemoveStaleScenes
      | Pop;
    type navigation = {
      send: action => unit,
      index: int
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
    module Animation = {
      type t = (state, int) => BsReactNative.Style.styleElement;
      let slideInOut: t =
        (state, idx) => {
          let width = float(Dimensions.get(`window)##width);
          Style.Transform.makeInterpolated(
            ~translateX=
              Animated.Value.interpolate(
                state.visibleScene,
                ~inputRange=[idx - 1, idx, idx + 1] |> List.map(float),
                ~outputRange=`float([-. width, 0.0, width *. 0.3]),
                ()
              ),
            ()
          );
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
        screens: [|{route: initialRoute, header: None, key: "0"}|],
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
          let index = Array.length(state.screens);
          let screen = {route, header: None, key: string_of_int(index)};
          ReasonReact.Update({
            ...state,
            activeScene: index,
            screens: state.screens |> Js.Array.concat([|screen|])
          });
        | Pop =>
          Array.length(state.screens) > 1 ?
            ReasonReact.Update({
              ...state,
              activeScene: state.activeScene - 1
            }) :
            ReasonReact.NoUpdate
        | RemoveStaleScenes =>
          ReasonReact.Update({
            ...state,
            screens:
              state.screens
              |> Js.Array.slice(~start=0, ~end_=state.activeScene + 1)
          })
        | SetHeaderOptions(idx, headerConfig) =>
          let screens = Js.Array.copy(state.screens);
          screens[idx] = {...screens[idx], header: Some(headerConfig)};
          ReasonReact.Update({...state, screens});
        },
      render: self =>
        self.state.screens
        |> Array.mapi((idx, screen: screenConfig) => {
             let width = float(Dimensions.get(`window)##width);
             let transform =
               Style.Transform.makeInterpolated(
                 ~translateX=
                   Animated.Value.interpolate(
                     self.state.visibleScene,
                     ~inputRange=[idx - 1, idx, idx + 1] |> List.map(float),
                     ~outputRange=`float([-. width, 0.0, width *. 0.3]),
                     ()
                   ),
                 ()
               );
             <Animated.View
               key=screen.key
               style=Style.(concat([Styles.card, style([transform])]))>
               (
                 switch screen.header {
                 | Some(config) => <Header config />
                 | None => <View />
                 }
               )
               <View style=Style.(style([flex(1.0)]))>
                 (
                   children(
                     ~currentRoute=screen.route,
                     ~navigation={send: self.send, index: idx}
                   )
                 )
               </View>
             </Animated.View>;
           })
        |> ReasonReact.arrayToElement
    };
  };
  module Screen = {
    open StackNavigator;
    let component = ReasonReact.statelessComponent("CallstackScreen");
    let make =
        (
          ~navigation: navigation,
          ~headerTitle=?,
          ~_animation=Animation.slideInOut,
          children
        ) => {
      ...component,
      didMount: _self => {
        navigation.send(
          SetHeaderOptions(navigation.index, {title: headerTitle})
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
