open BsReactNative;

open Utils;

module Styles = {
  open Style;
  let fill =
    style([
      position(Absolute),
      top(Pt(0.0)),
      left(Pt(0.0)),
      right(Pt(0.0)),
      bottom(Pt(0.0))
    ]);
  let card =
    style([
      backgroundColor("#E9E9EF"),
      shadowColor("black"),
      shadowOffset(~width=0.0, ~height=0.0),
      shadowOpacity(0.2),
      shadowRadius(5.0)
    ]);
};

module type NavigationConfig = {type route;};

module CreateNavigation = (Config: NavigationConfig) => {
  /**
   * Configure Animation module to receive additional payload for
   * configuration purposes.
   */
  include
    Animation.Create(
      {
        type options = (Config.route, Config.route);
      }
    );
  /**
   * StackNavigator
   */
  module StackNavigator = {
    module Header = {
      type t = {title: option(string)};
      let component = ReasonReact.statelessComponent("StackHeader");
      let make = (~config: t, _children) => {
        ...component,
        render: _self =>
          <View>
            <Text>
              (
                ReasonReact.stringToElement(
                  Js.Option.getWithDefault("", config.title)
                )
              )
            </Text>
          </View>
      };
    };
    type screenConfig = {
      route: Config.route,
      key: string,
      header: option(Header.t),
      animatedValue: Animated.Value.t,
      animation: Animation.t,
      style: Style.t
    };
    type state = {
      screens: array(screenConfig),
      activeScreen: int
    };
    type options = {
      header: option(Header.t),
      animation: option(Animation.t),
      style: option(Style.t)
    };
    type action =
      | Push(Config.route, string)
      | SetOptions(options, string)
      | RemoveStaleScreen(string)
      | Pop(string);
    type navigation = {
      push: Config.route => unit,
      setOptions: options => unit,
      pop: unit => unit
    };
    let component = ReasonReact.reducerComponent("StackNavigator");
    let isActiveScreen = (state, key) =>
      state.screens[state.activeScreen].key == key;
    let make = (~initialRoute, children) => {
      ...component,
      initialState: () => {
        screens: [|
          {
            route: initialRoute,
            header: None,
            animation: Animation.default,
            key: UUID.generate(),
            animatedValue: Animated.Value.create(0.0),
            style: Styles.card
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
            first.animatedValue |> second.animation(routes, action) |> fst;
          let sndAnim =
            second.animatedValue |> second.animation(routes, action) |> fst;
          let (fstValues, sndValues) =
            switch action {
            | Animation.Push => ((0.0, (-1.0)), (1.0, 0.0))
            | Animation.Pop => (((-1.0), 0.0), (0.0, 1.0))
            };
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
                  self.send(RemoveStaleScreen(second.key)) : (),
            ()
          );
          ();
        };
      },
      /***
       * StackNavigator router
       *
       * Most actions are indempotent and have `isActiveScreen(state, key)` check
       * to make sure we only accept one action from the screen that changes the
       * state.
       */
      reducer: (action, state) =>
        switch action {
        /***
         * Pushes new screen onto the stack
         *
         * Note: We push the item right after the active one (instead of always
         * adding to the end). This is to make sure no glitches happen when you
         * push in the middle of a pop.
         */
        | Push(route, key) =>
          if (isActiveScreen(state, key)) {
            let index = state.activeScreen + 1;
            ReasonReact.Update({
              activeScreen: index,
              screens:
                state.screens
                |> ReArray.append(
                     {
                       route,
                       header: None,
                       animation: Animation.default,
                       animatedValue: Animated.Value.create(1.0),
                       key: UUID.generate(),
                       style: Styles.card
                     },
                     index
                   )
            });
          } else {
            ReasonReact.NoUpdate;
          }
        /***
         * Pops screen from the stack
         */
        | Pop(key) =>
          if (state.activeScreen > 0 && isActiveScreen(state, key)) {
            ReasonReact.Update({
              ...state,
              activeScreen: state.activeScreen - 1
            });
          } else {
            ReasonReact.NoUpdate;
          }
        /***
         * Removes a stale screen from the stack w/o animation.
         *
         * This is usually done when the pop animation of particular screen
         * finishes and the screen is no longer within the viewport.
         */
        | RemoveStaleScreen(key) =>
          let idx =
            state.screens
            |> Js.Array.findIndex((screen: screenConfig) => screen.key == key);
          ReasonReact.Update({
            ...state,
            screens: state.screens |> ReArray.remove(idx)
          });
        /***
         * Sets option for a screen with a given key
         */
        | SetOptions({header, animation, style}, key) =>
          let screens = Js.Array.copy(state.screens);
          let idx =
            screens
            |> Js.Array.findIndex((screen: screenConfig) => screen.key == key);
          screens[idx] = {
            ...screens[idx],
            header,
            style: style |> Js.Option.getWithDefault(screens[idx].style),
            animation:
              animation |> Js.Option.getWithDefault(screens[idx].animation)
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
                 |> second.animation((first.route, second.route), action)
                 |> snd;
               };
             <Animated.View
               key=screen.key
               style=Style.(concat([Styles.fill, screen.style, animation]))>
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
                     ~navigation={
                       push: route => self.send(Push(route, screen.key)),
                       pop: () => self.send(Pop(screen.key)),
                       setOptions: opts =>
                         self.send(SetOptions(opts, screen.key))
                     }
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
        (
          ~navigation: navigation,
          ~style=?,
          ~headerTitle=?,
          ~animation=?,
          children
        ) => {
      ...component,
      didMount: _self => {
        navigation.setOptions({
          header: Some({title: headerTitle}),
          animation,
          style
        });
        ReasonReact.NoUpdate;
      },
      render: _self => {
        let body = children();
        <View> body </View>;
      }
    };
  };
};