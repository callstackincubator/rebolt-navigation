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
    module Animation = {
      type action =
        | Push
        | Pop;
      type options = {
        transition: (Config.route, Config.route),
        action,
        index: int
      };
      type t =
        (options, BsReactNative.Animated.Value.t) =>
        BsReactNative.Style.styleElement;
      let slideInOut: t =
        ({index}, value) => {
          let width = float(Dimensions.get(`window)##width);
          Style.Transform.makeInterpolated(
            ~translateX=
              Animated.Value.interpolate(
                value,
                ~inputRange=[index - 1, index, index + 1] |> List.map(float),
                ~outputRange=`float([-. width, 0.0, width *. 0.3]),
                ()
              ),
            ()
          );
        };
      let fadeInOut: t =
        ({index}, value) =>
          Style.(
            opacity(
              Interpolated(
                Animated.Value.interpolate(
                  value,
                  ~inputRange=[index - 1, index, index + 1] |> List.map(float),
                  ~outputRange=`float([0.0, 1.0, 0.0]),
                  ()
                )
              )
            )
          );
    };
    type headerConfig = {title: option(string)};
    type animationConfig = Animation.t;
    type screenConfig = {
      route: Config.route,
      key: string,
      header: option(headerConfig),
      animation: option(animationConfig)
    };
    type state = {
      screens: array(screenConfig),
      activeScene: int,
      visibleScene: Animated.Value.t
    };
    type action =
      | Push(Config.route)
      | SetOptions(int, option(headerConfig), option(animationConfig))
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
        screens: [|
          {route: initialRoute, header: None, animation: None, key: "0"}
        |],
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
          let screen = {
            route,
            header: None,
            animation: None,
            key: string_of_int(index)
          };
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
        | SetOptions(idx, headerConfig, animationConfig) =>
          let screens = Js.Array.copy(state.screens);
          screens[idx] = {
            ...screens[idx],
            header: headerConfig,
            animation: animationConfig
          };
          ReasonReact.Update({...state, screens});
        },
      render: self =>
        self.state.screens
        |> Array.mapi((idx, screen: screenConfig) => {
             let animation =
               switch screen.animation {
               | Some(generate) =>
                 let len = Array.length(self.state.screens);
                 if (len < 2) {
                   [];
                 } else {
                   let (fromRouteIdx, toRouteIdx) =
                     idx == len - 1 ? (idx, idx - 1) : (idx, idx + 1);
                   let isPushing = self.state.activeScene + 1 == len;
                   [
                     generate(
                       {
                         transition: (
                           self.state.screens[fromRouteIdx].route,
                           self.state.screens[toRouteIdx].route
                         ),
                         action: isPushing ? Animation.Push : Animation.Pop,
                         index: idx
                       },
                       self.state.visibleScene
                     )
                   ];
                 };
               | None => []
               };
             <Animated.View
               key=screen.key
               style=Style.(concat([Styles.card, style(animation)]))>
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
        (~navigation: navigation, ~headerTitle=?, ~animation=?, children) => {
      ...component,
      didMount: _self => {
        navigation.send(
          SetOptions(navigation.index, Some({title: headerTitle}), animation)
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
