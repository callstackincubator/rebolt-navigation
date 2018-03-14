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
      type direction =
        | In
        | Out;
      type options = {
        routes: (Config.route, Config.route),
        direction,
        action
      };
      type config =
        (
          ~value: Animated.Value.value,
          ~toValue: [ | `animated(Animated.Value.value) | `raw(float)]
        ) =>
        Animated.CompositeAnimation.t;
      type t = (options, Animated.Value.t) => (config, Style.t);
      let slideInOut: t =
        (opts, value) => {
          let screenWidth = float(Dimensions.get(`window)##width);
          (
            Animated.Spring.animate(
              ~stiffness=100.0,
              ~damping=500.0,
              ~mass=3.0,
              ()
            ),
            Style.(
              style([
                Transform.makeInterpolated(
                  ~translateX=
                    Animated.Value.interpolate(
                      value,
                      ~inputRange=[0, 1] |> List.map(float),
                      ~outputRange=
                        `float(
                          switch (opts.action, opts.direction) {
                          | (Pop, Out) => [0.0, screenWidth]
                          | (Push, In) => [screenWidth, 0.0]
                          | (Pop, In) => [-. screenWidth *. 0.3, 0.0]
                          | (Push, Out) => [0.0, -. screenWidth *. 0.3]
                          }
                        ),
                      ()
                    ),
                  ()
                )
              ])
            )
          );
        };
      let fadeInOut: t =
        (opts, value) => (
          Animated.Timing.animate(~duration=300.0, ()),
          Style.(
            style([
              opacity(
                Interpolated(
                  Animated.Value.interpolate(
                    value,
                    ~inputRange=[0, 1] |> List.map(float),
                    ~outputRange=
                      `float(opts.direction == In ? [0.0, 1.0] : [1.0, 0.0]),
                    ()
                  )
                )
              )
            ])
          )
        );
      let default = slideInOut;
      let none: t =
        (opts, value) => (
          Animated.Timing.animate(~duration=0.0, ()),
          fadeInOut(opts, value) |> snd
        );
    };
    type headerConfig = {title: option(string)};
    type animationConfig = Animation.t;
    type screenConfig = {
      route: Config.route,
      key: string,
      header: option(headerConfig),
      animatedValue: Animated.Value.t,
      animation: Animation.t
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
            animation: Animation.default,
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
          let (first, second) =
            fromIdx < toIdx ?
              (self.state.screens[fromIdx], self.state.screens[toIdx]) :
              (self.state.screens[toIdx], self.state.screens[fromIdx]);
          let action = fromIdx < toIdx ? Animation.Push : Animation.Pop;
          let routes = (first.route, second.route);
          let fstAnim =
            first.animatedValue
            |> second.animation({
                 routes,
                 action,
                 direction:
                   action == Animation.Push ? Animation.Out : Animation.In
               })
            |> fst;
          let sndAnim =
            second.animatedValue
            |> second.animation({
                 routes,
                 action,
                 direction:
                   action == Animation.Push ? Animation.In : Animation.Out
               })
            |> fst;
          Animated.Value.setValue(first.animatedValue, 0.0);
          Animated.Value.setValue(second.animatedValue, 0.0);
          Animated.(
            CompositeAnimation.start(
              parallel(
                [|
                  fstAnim(~value=first.animatedValue, ~toValue=`raw(1.0)),
                  sndAnim(~value=second.animatedValue, ~toValue=`raw(1.0))
                |],
                {"stopTogether": Js.Boolean.to_js_boolean(false)}
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
            animation: Animation.default,
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
            animation:
              animationConfig
              |> Js.Option.getWithDefault(screens[idx].animation)
          };
          ReasonReact.Update({...state, screens});
        },
      render: self => {
        let size = Array.length(self.state.screens);
        let action =
          self.state.activeScreen + 1 < size ? Animation.Pop : Animation.Push;
        self.state.screens
        |> Array.mapi((idx, screen: screenConfig) => {
             let isNotVisible = idx + 2 < size;
             let animation =
               /**
								 * As a performance optimisation, we don't animate nor display
								 * any screen but the two last one.
								 */
               (
                 if (isNotVisible || size == 1) {
                   Style.style([]);
                 } else {
                   let isLast = idx + 1 == size;
                   let (first, second) =
                     isLast ?
                       (self.state.screens[idx - 1], screen) :
                       (screen, self.state.screens[idx + 1]);
                   screen.animatedValue
                   |> second.animation({
                        routes: (first.route, second.route),
                        action,
                        direction:
                          switch (action, isLast) {
                          | (Animation.Push, true)
                          | (Animation.Pop, false) => Animation.In
                          | _ => Animation.Out
                          }
                      })
                   |> snd;
                 }
               );
             <Animated.View
               key=screen.key style=Style.(concat([Styles.card, animation]))>
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
