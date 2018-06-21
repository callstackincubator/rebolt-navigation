/** Header configuration object */
type config = {
  style: option(Rebolt.Style.t),
  title: option(string),
  center: option(returnsComponent),
  left: option(returnsComponent),
  right: option(returnsComponent),
}
and returnsComponent = props => ReasonReact.reactElement
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
  animatedValue: Rebolt.Animated.Interpolation.t,
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