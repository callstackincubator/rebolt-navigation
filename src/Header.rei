type config = {title: option(string)};

type screenConfig = {
  header: config,
  animation: Animation.t,
  key: string
};

let default: config;

module FloatingHeader: {
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
      ~screens: array(screenConfig),
      ~activeScreen: int,
      ~animatedValue: BsReactNative.Animated.Value.t,
      ~pop: string => unit,
      'a
    ) =>
    ReasonReact.componentSpec(
      ReasonReact.stateless,
      ReasonReact.stateless,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      ReasonReact.actionless
    );
};

module PlatformHeader = FloatingHeader;