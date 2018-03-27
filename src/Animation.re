open BsReactNative;

module type AnimationConfig = {
  /**
   * Options object is passed to every animation in order to generate
   * the style and easing function to apply in context of particular two screens
   * and interaction that happens between them.
   */
  type options;
};

/**
 * Animation module
 */
module Create = (Config: AnimationConfig) => {
  module Animation = {
    /**
     * Animation type
     *
     * First element is partially applied Animated function (e.g. Spring)
     * that specifies the configuration of the animation to use.
     *
     * Note that `value` and `toValue` are applied later by current navigator.
     *
     * Second element is a React Native style element that is applied to
     * `Animated.View` container of the current scene.
     */
    type t = {
      func:
        (
          ~value: Animated.Value.value,
          ~toValue: [ | `animated(Animated.Value.value) | `raw(float)]
        ) =>
        Animated.CompositeAnimation.t,
      forCard: (Config.options, Animated.Value.t) => Style.t
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
      }
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
      forCard: (_options, _value) => Style.style([])
    };
  };
};