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
      type config =
        (
          ~value: Animated.Value.value,
          ~toValue: [ | `animated(Animated.Value.value) | `raw(float)]
        ) =>
        Animated.CompositeAnimation.t;
      type t = (options, Animated.Value.t) => (config, Style.t);
      let slideInOut: t =
        (_opts, value) => {
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
                      ~inputRange=[(-1), 0, 1] |> List.map(float),
                      ~outputRange=
                        `float([-. screenWidth *. 0.3, 0.0, screenWidth]),
                      ()
                    ),
                  ()
                )
              ])
            )
          );
        };
      let fadeInOut: t =
        (_opts, value) => (
          Animated.Timing.animate(~duration=300.0, ()),
          Style.(
            style([
              opacity(
                Interpolated(
                  Animated.Value.interpolate(
                    value,
                    ~inputRange=[(-1), 0, 1] |> List.map(float),
                    ~outputRange=`float([0.0, 1.0, 0.0]),
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
      | RemoveStaleScreen(int)
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
            animatedValue: Animated.Value.create(0.0)
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
            first.animatedValue |> second.animation({routes, action}) |> fst;
          let sndAnim =
            second.animatedValue |> second.animation({routes, action}) |> fst;
          let (fstValues, sndValues) =
            switch action {
            | Animation.Push => ((0.0, (-1.0)), (1.0, 0.0))
            | Animation.Pop => (((-1.0), 0.0), (0.0, 1.0))
						};
					Animated.Value.stopAnimation(first.animatedValue);
					Animated.Value.stopAnimation(second.animatedValue);
          Animated.CompositeAnimation.start(
            Animated.parallel(
              [|
                fstAnim(
                  ~value=first.animatedValue,
                  ~toValue=`raw(fstValues |> snd)
                ),
                sndAnim(
                  ~value=second.animatedValue,
                  ~toValue=`raw(sndValues |> snd)
                )
              |],
              {"stopTogether": Js.Boolean.to_js_boolean(false)}
            ),
            ~callback=
              end_ =>
                action == Animation.Pop && Js.to_bool(end_##finished) ?
                  self.send(RemoveStaleScreen(fromIdx)) : (),
            ()
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
            animatedValue: Animated.Value.create(1.0),
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
        | RemoveStaleScreen(idx) =>
          let screens = Js.Array.copy(state.screens);
          Js.Array.spliceInPlace(~pos=idx, ~remove=1, ~add=[||], screens);
          ReasonReact.Update({...state, screens});
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
             let animation =
               if (size == 1) {
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
                      action
                    })
                 |> snd;
               };
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
