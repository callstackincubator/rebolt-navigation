open BsReactNative;

open Utils;

module type NavigationConfig = {type route;};

module CreateNavigation = (Config: NavigationConfig) => {
  include
    Animation.Create(
      {
        type options = (Config.route, Config.route);
      }
    );
  module StackNavigator = {
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
      | SetOptions(string, option(headerConfig), option(animationConfig))
      | RemoveStaleScreen(string)
      | Pop;
    type navigation = {
      send: action => unit,
      key: string
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
            key: UUID.generate(),
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
      reducer: (action, state) =>
        switch action {
        | Push(route) =>
          let index = state.activeScreen + 1;
          let screens = Js.Array.copy(state.screens);
          let screen = {
            route,
            header: None,
            animation: Animation.default,
            animatedValue: Animated.Value.create(1.0),
            key: UUID.generate()
          };
          let _ignored =
            screens
            |> Js.Array.spliceInPlace(~pos=index, ~remove=0, ~add=[|screen|]);
          ReasonReact.Update({activeScreen: index, screens});
        | Pop =>
          state.activeScreen > 0 ?
            ReasonReact.Update({
              ...state,
              activeScreen: state.activeScreen - 1
            }) :
            ReasonReact.NoUpdate
        | RemoveStaleScreen(key) =>
          let screens = Js.Array.copy(state.screens);
          let idx =
            screens
            |> Js.Array.findIndex((screen: screenConfig) => screen.key == key);
          let _removed =
            Js.Array.spliceInPlace(~pos=idx, ~remove=1, ~add=[||], screens);
          ReasonReact.Update({...state, screens});
        | SetOptions(key, headerConfig, animationConfig) =>
          let screens = Js.Array.copy(state.screens);
          let idx =
            screens
            |> Js.Array.findIndex((screen: screenConfig) => screen.key == key);
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
                 |> second.animation((first.route, second.route), action)
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
                     ~navigation={send: self.send, key: screen.key}
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
          SetOptions(navigation.key, Some({title: headerTitle}), animation)
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
