/** Header configuration object */
type config = {
  title: option(string),
  renderHeaderTitle: option(returnsComponent),
  renderHeaderLeft: option(returnsComponent),
  renderHeaderRight: option(returnsComponent),
}
/** Getter for parts of the header */
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