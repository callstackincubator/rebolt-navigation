type stringOrElement = [ | `string(string) | `render((unit) => ReasonReact.reactElement)];
type element = [ | `render((unit) => ReasonReact.reactElement)];

/** Header configuration object */
type config = {
  style: option(BsReactNative.Style.t),
  title: option(stringOrElement),
  left: option(stringOrElement),
  right: option(element),
}
/** Screen object  */
and screen = {
  header: config,
  animation: Animation.t,
  key: string,
}
/** Header props */
and props = {
  screens: array(screen),
  activeScreen: int,
  animatedValue: BsReactNative.Animated.Value.t,
  pop: string => unit,
};

let default: config;

/**
 * Default implementation of Header on iOS
 */
module IOS: {
  let make:
    (~headerProps: props, 'a) =>
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
    (~headerProps: props, 'a) =>
    ReasonReact.componentSpec(
      ReasonReact.stateless,
      ReasonReact.stateless,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      ReasonReact.actionless,
    );
};