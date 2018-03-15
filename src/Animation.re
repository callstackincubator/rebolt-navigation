open BsReactNative;

open ReRouteTypes;

module Create = (Config: NavigationConfig) => {
  module Animation = {
    /**
     * Animation can happen as a result of either `Push` or `Pop`
     */
    type action =
      | Push
      | Pop;
    /**
     * Options object is passed to every animation in order to generate
     * the style and easing function to apply in context of particular two screens
     * and interaction that happens between them.
     *
     * The `routes` tuple contains a pair of routes next to each other on stack.
     * Action describes the interaction that happens between them.
     *
     * When `action` is of type `Push`, the second element is added onto the stack.
     * Otherwise, the second element is being removed.
     */
    type options = {
      routes: (Config.route, Config.route),
      action
    };
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
    type t =
      (options, Animated.Value.t) =>
      (
        (
          ~value: Animated.Value.value,
          ~toValue: [ | `animated(Animated.Value.value) | `raw(float)]
        ) =>
        Animated.CompositeAnimation.t,
        Style.t
      );
    /**
     * Slide in/out animation modelled after iOS platform interactions
     */
    let slideInOut = (_opts, value) => {
      let screenWidth = float(Dimensions.get(`window)##width);
      (
        Animated.Spring.animate(
          ~stiffness=100.0,
          ~damping=500.0,
          ~mass=3.0,
          ~useNativeDriver=Js.Boolean.to_js_boolean(true),
          ()
        ),
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
        )
      );
    };
    /**
     * Simple fade in out animation
     */
    let fadeInOut = (_opts, value) => (
      Animated.Timing.animate(~duration=300.0, ()),
      Style.(
        style([
          opacity(
            Interpolated(
              Animated.Value.interpolate(
                value,
                ~inputRange=[(-1), 0, 1] |> List.map(float),
                ~outputRange=`float([0.0, 1.0, 0.0]),
                ()
              )
            )
          )
        ])
      )
    );
    /**
     * Platform-specific default animation that is picked by navigators when
     * nothing else is set
     */
    let default = slideInOut;
    /**
     * No animation
     */
    let none = (opts, value) => (
      Animated.Timing.animate(~duration=0.0, ()),
      fadeInOut(opts, value) |> snd
    );
  };
};
