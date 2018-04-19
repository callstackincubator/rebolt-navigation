/**
 * Header config
 */
type config = {title: option(string)};

/**
 * Screen config that is used by this Header
 */
type screenConfig = {
  header: config,
  animation: Animation.t,
  key: string,
};

/**
 * Default configuration used on Screen that is mounting or has
 * no Screen component inside
 */
let default: config;

/**
 * Default implementation of Header on iOS
 */
module IOS: {
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
      ReasonReact.actionless,
    );
};

module Android: {
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
      ReasonReact.actionless,
    );
};