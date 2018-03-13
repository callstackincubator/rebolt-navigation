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
        action
      };
      type style = Style.styleElement;
      type config =
        (
          ~value: Animated.Value.value,
          ~toValue: [ | `animated(Animated.Value.value) | `raw(float)]
        ) =>
        Animated.CompositeAnimation.t;
      type t = (options, Animated.Value.t) => (config, style);
      let defaultConfig = Animated.Timing.animate(~duration=300.0, ());
      let slideInOut: t =
        (_opts, value) => {
          let width = float(Dimensions.get(`window)##width);
          (
            defaultConfig,
            Style.Transform.makeInterpolated(
              ~translateX=
                Animated.Value.interpolate(
                  value,
                  ~inputRange=[0, 1] |> List.map(float),
                  ~outputRange=`float([width, 0.0]),
                  ()
                ),
              ()
            )
          );
        };
      let fadeInOut: t =
        (_opts, value) => (
          defaultConfig,
          Style.(
            opacity(
              Interpolated(
                Animated.Value.interpolate(
                  value,
                  ~inputRange=[0, 1] |> List.map(float),
                  ~outputRange=`float([0.0, 1.0]),
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
      animatedValue: Animated.Value.t,
      animation: option(Animation.t)
    };
    type state = {
      screens: array(screenConfig),
      activeScreen: int
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
          {
            route: initialRoute,
            header: None,
            animation: None,
            key: "0",
            animatedValue: Animated.Value.create(1.0)
          }
        |],
        activeScreen: 0
      },
      didUpdate: ({oldSelf, newSelf: self}) => {
        let fromIdx = oldSelf.state.activeScreen;
        let toIdx = self.state.activeScreen;
        if (fromIdx !== toIdx) {
          let fromScreen = self.state.screens[fromIdx];
          let toScreen = self.state.screens[toIdx];
          let (action, routes) =
            fromIdx < toIdx ?
              (Animation.Push, (fromScreen.route, toScreen.route)) :
              (Animation.Pop, (toScreen.route, fromScreen.route));
          let fromAnimation =
            switch fromScreen.animation {
            | Some(generate) =>
              fromScreen.animatedValue |> generate({routes, action}) |> fst
            | None => Animation.defaultConfig
            };
          let toAnimation =
            switch toScreen.animation {
            | Some(generate) =>
              toScreen.animatedValue |> generate({routes, action}) |> fst
            | None => Animation.defaultConfig
            };
          Animated.Value.setValue(fromScreen.animatedValue, 1.0);
          Animated.Value.setValue(toScreen.animatedValue, 0.0);
          Animated.(
            CompositeAnimation.start(
              parallel(
                [|
                  fromAnimation(
                    ~value=fromScreen.animatedValue,
                    ~toValue=`raw(0.0)
                  ),
                  toAnimation(
                    ~value=toScreen.animatedValue,
                    ~toValue=`raw(1.0)
                  )
                |],
                {"stopTogether": Js.Boolean.to_js_boolean(true)}
              ),
              ~callback=_end => self.send(RemoveStaleScreens),
              ()
            )
          );
          ();
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
            animatedValue: Animated.Value.create(0.0),
            key: string_of_int(index)
          };
          ReasonReact.Update({
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
      render: self => {
        let size = Array.length(self.state.screens);
        let action =
          self.state.activeScreen <= size ? Animation.Pop : Animation.Push;
        self.state.screens
        |> Array.mapi((idx, screen: screenConfig) => {
             let animation =
               switch screen.animation {
               | Some(generate) =>
                 if (size < 2) {
                   [];
                 } else {
                   let routes =
                     idx == size - 1 ?
                       (self.state.screens[idx - 1].route, screen.route) :
                       (screen.route, self.state.screens[idx + 1].route);
                   [screen.animatedValue |> generate({routes, action}) |> snd];
                 }
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
        |> ReasonReact.arrayToElement;
      }
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
