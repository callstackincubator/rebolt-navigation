module CreateStackNavigator:
  (Config: {type route;}) =>
  {
    module StackNavigator: {
      type state;
      type options;
      type action;
      type navigation = {
        push: Config.route => unit,
        setOptions: options => unit,
        pop: unit => unit,
      };
      let make:
        (
          ~initialRoute: Config.route,
          ~headerComponent: (
                              ~screens: array(Header.screenConfig),
                              ~activeScreen: int,
                              ~animatedValue: BsReactNative.Animated.Value.t,
                              ~pop: string => unit,
                              array('a)
                            ) =>
                            ReasonReact.component(
                              ReasonReact.stateless,
                              ReasonReact.noRetainedProps,
                              ReasonReact.actionless,
                            )
                              =?,
          (~currentRoute: Config.route, ~navigation: navigation) =>
          ReasonReact.reactElement
        ) =>
        ReasonReact.componentSpec(
          state,
          state,
          ReasonReact.noRetainedProps,
          ReasonReact.noRetainedProps,
          action,
        );
      module Animation = Animation;
      module Screen: {
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
            ReasonReact.actionless,
          );
      };
    };
  };