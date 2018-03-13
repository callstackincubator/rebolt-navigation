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
        routes: (Config.route, Config.route),
        action,
        index: int
      };
      type style = BsReactNative.Style.styleElement;
      type animationConfig = {duration: float};
      type t =
        (options, BsReactNative.Animated.Value.t) => (animationConfig, style);
      let defaultConfig = {duration: 300.0};
      let slideInOut: t =
        ({index}, value) => {
          let width = float(Dimensions.get(`window)##width);
          (
            {duration: 300.0},
            Style.Transform.makeInterpolated(
              ~translateX=
                Animated.Value.interpolate(
                  value,
                  ~inputRange=[index - 1, index, index + 1] |> List.map(float),
                  ~outputRange=`float([-. width, 0.0, width *. 0.3]),
                  ()
                ),
              ()
            )
          );
        };
      let fadeInOut: t =
        ({index}, value) => (
          {duration: 100.0},
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
      activeScreen: int,
      animatedIndex: Animated.Value.t
    };
    type action =
      | Push(Config.route)
      | SetOptions(int, option(headerConfig), option(animationConfig))
      | RemoveStaleScreens
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
        activeScreen: 0,
        animatedIndex: Animated.Value.create(0.0)
      },
      didUpdate: ({oldSelf, newSelf: self}) => {
        let fromIdx = oldSelf.state.activeScreen;
        let toIdx = self.state.activeScreen;
        if (fromIdx != toIdx) {
          let isPushing = fromIdx < toIdx;
          let action = isPushing ? Animation.Push : Animation.Pop;
          let routes =
            isPushing ?
              (
                self.state.screens[fromIdx].route,
                self.state.screens[toIdx].route
              ) :
              (
                self.state.screens[toIdx].route,
                self.state.screens[fromIdx].route
              );
          let fromConfig =
            switch self.state.screens[fromIdx].animation {
            | Some(generate) =>
              self.state.animatedIndex
              |> generate({routes, index: fromIdx, action})
              |> fst
            | None => Animation.defaultConfig
            };
          let toConfig =
            switch self.state.screens[toIdx].animation {
            | Some(generate) =>
              self.state.animatedIndex
              |> generate({routes, index: toIdx, action})
              |> fst
            | None => Animation.defaultConfig
            };
          Animated.(
            CompositeAnimation.start(
              Timing.animate(
                ~value=self.state.animatedIndex,
                ~duration=fromConfig.duration,
                ~toValue=`raw(float_of_int(self.state.activeScreen)),
                ()
              ),
              ~callback=_end => self.send(RemoveStaleScreens),
              ()
            )
          );
        };
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
            activeScreen: index,
            screens: state.screens |> Js.Array.concat([|screen|])
          });
        | Pop =>
          Array.length(state.screens) > 1 ?
            ReasonReact.Update({
              ...state,
              activeScreen: state.activeScreen - 1
            }) :
            ReasonReact.NoUpdate
        | RemoveStaleScreens =>
          ReasonReact.Update({
            ...state,
            screens:
              state.screens
              |> Js.Array.slice(~start=0, ~end_=state.activeScreen + 1)
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
                   let isPushing = self.state.activeScreen + 1 == len;
                   [
                     self.state.animatedIndex
                     |> generate({
                          routes: (
                            self.state.screens[fromRouteIdx].route,
                            self.state.screens[toRouteIdx].route
                          ),
                          action: isPushing ? Animation.Push : Animation.Pop,
                          index: idx
                        })
                     |> snd
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
