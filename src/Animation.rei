/**
 * Animation type
 *
 * Lots of logic used for `forX` interpolators has been inspired and borrowed by
 * great work by React Navigation team.
 *
 * You can browse their implementation on Github:
 * - /src/views/Header/HeaderStyleInterpolator.js
 */
type t = {
  func:
    (
      ~value: Rebolt.Animated.Value.t,
      ~toValue: [ | `animated(Rebolt.Animated.Value.t) | `raw(float)]
    ) =>
    Rebolt.Animated.CompositeAnimation.t,
  forCard: 'a .Rebolt.Animated.node('a) => Rebolt.Style.t,
  forHeader: 'a .Rebolt.Animated.node('a) => Rebolt.Style.t,
};

/**
 * Slide in/out animation modelled after iOS platform interactions
 */
let slideHorizontal: t;

let fadeVertical: t;

/**
 * Platform-specific default animation that is picked by navigators when
 * nothing else is set
 */
let default: t;

/**
 * No animation
 */
let none: t;