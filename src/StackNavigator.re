open BsReactNative;

open ReRouteTypes;

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
  let flex = style([flex(1.0)]);
  let card =
    style([
      backgroundColor(String("#E9E9EF")),
      shadowColor(String("black")),
      shadowOffset(~width=0.0, ~height=0.0),
      shadowOpacity(0.2),
      shadowRadius(5.0)
    ]);
  let stackContainer = concat([flex, style([flexDirection(ColumnReverse)])]);
};

module CreateStackNavigator = (Config: NavigationConfig) => {
  module StackNavigator = {
    type headerConfig = {title: option(string)};
    type screenConfig = {
      route: Config.route,
      key: string,
      header: Header.config,
      animatedValue: Animated.Value.t,
      animation: Animation.t,
      style: Style.t
    };
    type state = {
      screens: array(screenConfig),
      headerAnimatedValue: Animated.Value.t,
      activeScreen: int
    };
    type options = {
      header: Header.config,
      animation: option(Animation.t),
      style: option(Style.t)
    };
    type action =
      | PushScreen(Config.route, string)
      | SetOptions(options, string)
      | RemoveStaleScreen(string)
      | PopScreen(string);
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
            header: Header.default,
            animation: Animation.default,
            key: UUID.generate(),
            animatedValue: Animated.Value.create(0.0),
            style: Styles.card
          }
        |],
        activeScreen: 0,
        headerAnimatedValue: Animated.Value.create(0.0)
      },
      /***
       * Begin animating two states as soon as the index changes
       *
       * The animation is configured based on the latter screen. That said,
       * when screen B (being removed) uses `fade` transition, the screen
       * that is to appear will fade in (even though it doesn't define custom
       * animation itself).
       *
       * Values -1, 0, 1 describe position on screen. Screen with value `0` is the
       * one that is currently visible. Screen with "1" is rendered and hidden on the
       * right hand side whereas "-1" is hidden on the left hand side.
       *
       * Example:
       * 0 to -1 -> next screen has been pushed
       * 0 to 1 -> this screen is getting popped
       * -1 to 0 -> next screen has been popped
       * 1 to 0 -> this screen has been pushed
       */
      didUpdate: ({oldSelf, newSelf: self}) => {
        let fromIdx = oldSelf.state.activeScreen;
        let toIdx = self.state.activeScreen;
        if (fromIdx !== toIdx) {
          let (first, second) =
            fromIdx < toIdx ?
              (self.state.screens[fromIdx], self.state.screens[toIdx]) :
              (self.state.screens[toIdx], self.state.screens[fromIdx]);
          let action = fromIdx < toIdx ? `Push : `Pop;
          let (fstValues, sndValues) =
            switch action {
            | `Push => ((0.0, (-1.0)), (1.0, 0.0))
            | `Pop => (((-1.0), 0.0), (0.0, 1.0))
            };
          Animated.CompositeAnimation.start(
            Animated.parallel(
              [|
                second.animation.func(
                  ~value=self.state.headerAnimatedValue,
                  ~toValue=`raw(float_of_int(toIdx))
                ),
                second.animation.func(
                  ~value=first.animatedValue,
                  ~toValue=`raw(fstValues |> snd)
                ),
                second.animation.func(
                  ~value=second.animatedValue,
                  ~toValue=`raw(sndValues |> snd)
                )
              |],
              {"stopTogether": Js.Boolean.to_js_boolean(false)}
            ),
            ~callback=
              end_ =>
                action == `Pop && Js.to_bool(end_##finished) ?
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
        | PushScreen(route, key) =>
          if (isActiveScreen(state, key)) {
            let index = state.activeScreen + 1;
            ReasonReact.Update({
              ...state,
              activeScreen: index,
              screens:
                state.screens
                |> ReArray.append(
                     {
                       route,
                       header: Header.default,
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
        | PopScreen(key) =>
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
        <View style=Styles.stackContainer>
          <View style=Styles.flex>
            (
              self.state.screens
              |> Array.mapi((idx, screen: screenConfig) => {
                   let animation =
                     if (size == 1) {
                       Style.style([]);
                     } else {
                       let scr =
                         idx + 1 == size ?
                           screen : self.state.screens[idx + 1];
                       screen.animatedValue
                       |> scr.animation.forCard({idx: idx});
                     };
                   <Animated.View
                     key=screen.key
                     style=Style.(
                             concat([Styles.fill, screen.style, animation])
                           )>
                     <View>
                       (
                         children(
                           ~currentRoute=screen.route,
                           ~navigation={
                             push: route =>
                               self.send(PushScreen(route, screen.key)),
                             pop: () => self.send(PopScreen(screen.key)),
                             setOptions: opts =>
                               self.send(SetOptions(opts, screen.key))
                           }
                         )
                       )
                     </View>
                   </Animated.View>;
                 })
              |> ReasonReact.arrayToElement
            )
          </View>
          <Header.PlatformHeader
            animatedValue=self.state.headerAnimatedValue
            pop=(key => self.send(PopScreen(key)))
            activeScreen=self.state.activeScreen
            screens=(
              self.state.screens
              |> Array.map((scr: screenConfig) =>
                   {
                     Header.header: scr.header,
                     animation: scr.animation,
                     key: scr.key
                   }
                 )
            )
          />
        </View>;
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
          header: {
            title: headerTitle
          },
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