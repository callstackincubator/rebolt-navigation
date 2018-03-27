open BsReactNative;

type options = { idx: int };

/**
 * Interpolates style
 */
type interpolator = (options, Animated.Value.t) => Style.t;

/**
 * Animation type
 */
type t = {
  /** Partially applied Animated function to use for particular transition */
  func:
    (
      ~value: Animated.Value.value,
      ~toValue: [ | `animated(Animated.Value.value) | `raw(float)]
    ) =>
    Animated.CompositeAnimation.t,
  /** Card style interpolator */
  forCard: interpolator,
  /** Header center area interpolator */
  forHeaderCenter: interpolator
};

/**
 * Slide in/out animation modelled after iOS platform interactions
 */
let slideInOut = {
  func:
    Animated.Spring.animate(
      ~stiffness=100.0,
      ~damping=500.0,
      ~mass=3.0,
      ~useNativeDriver=Js.Boolean.to_js_boolean(true),
      ()
    ),
  forCard: (_options, value) => {
    let screenWidth = float(Dimensions.get(`window)##width);
    Style.(
      style([
        opacity(
          Interpolated(
            Animated.Value.interpolate(
              value,
              ~inputRange=[(-1.0), (-0.99), 0.0, 0.99, 1.0],
              ~outputRange=`float([0.0, 1.0, 1.0, 0.85, 0.0]),
              ()
            )
          )
        ),
        Transform.makeInterpolated(
          ~translateX=
            Animated.Value.interpolate(
              value,
              ~inputRange=[(-1), 0, 1] |> List.map(float),
              ~outputRange=
                `float([-. screenWidth *. 0.3, 0.0, screenWidth]),
              ()
            ),
          ()
        )
      ])
    );
  },
  forHeaderCenter: (_opts, _value) => Style.style([])
};
/**
 * Platform-specific default animation that is picked by navigators when
 * nothing else is set
 */
let default = slideInOut;
/**
 * No animation
 */
let none = {
  func: Animated.Timing.animate(~duration=0.0, ()),
  forCard: (_options, _value) => Style.style([]),
  forHeaderCenter: (_opts, _value) => Style.style([])
};