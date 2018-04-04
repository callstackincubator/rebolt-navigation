module CreateStackNavigator:
  (Config: ReRouteTypes.NavigationConfig) =>
  {
    module StackNavigator: {
      type screenConfig = {
        route: Config.route,
        key: string,
        header: Header.config,
        animatedValue: BsReactNative.Animated.Value.t,
        animation: Animation.t,
        style: BsReactNative.Style.t
      };
      type state = {
        screens: array(screenConfig),
        activeScreen: int
      };
      type options = {
        header: Header.config,
        animation: option(Animation.t),
        style: option(BsReactNative.Style.t)
      };
      type action =
        | PushScreen(Config.route, string)
        | SetOptions(options, string)
        | RemoveStaleScreen(string)
        | RemoveLastScreen
        | PopScreen(string);
      type navigation = {
        push: Config.route => unit,
        setOptions: options => unit,
        pop: unit => unit
      };
      let component:
        ReasonReact.componentSpec(
          state,
          ReasonReact.stateless,
          ReasonReact.noRetainedProps,
          ReasonReact.noRetainedProps,
          action
        );
      let make:
        (
          ~initialRoute: Config.route,
          (~currentRoute: Config.route, ~navigation: navigation) =>
          ReasonReact.reactElement
        ) =>
        ReasonReact.componentSpec(
          state,
          state,
          ReasonReact.noRetainedProps,
          ReasonReact.noRetainedProps,
          action
        );
      module Screen: {
        let component:
          ReasonReact.componentSpec(
            ReasonReact.stateless,
            ReasonReact.stateless,
            ReasonReact.noRetainedProps,
            ReasonReact.noRetainedProps,
            ReasonReact.actionless
          );
        let make:
          (
            ~navigation: navigation,
            ~style: BsReactNative.Style.t=?,
            ~headerTitle: string=?,
            ~animation: Animation.t=?,
            unit => ReasonReact.reactElement
          ) =>
          ReasonReact.componentSpec(
            ReasonReact.stateless,
            ReasonReact.stateless,
            ReasonReact.noRetainedProps,
            ReasonReact.noRetainedProps,
            ReasonReact.actionless
          );
      };
    };
  };