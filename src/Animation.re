open BsReactNative;

open ReRouteTypes;

module Create = (Config: NavigationConfig) => {
  module Animation = {
    type action =
      | Push
      | Pop;
    type options = {
      routes: (Config.route, Config.route),
      action
    };
    type config =
      (
        ~value: Animated.Value.value,
        ~toValue: [ | `animated(Animated.Value.value) | `raw(float)]
      ) =>
      Animated.CompositeAnimation.t;
    type t = (options, Animated.Value.t) => (config, Style.t);
    let slideInOut: t =
      (_opts, value) => {
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
    let fadeInOut: t =
      (_opts, value) => (
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
    let default = slideInOut;
    let none: t =
      (opts, value) => (
        Animated.Timing.animate(~duration=0.0, ()),
        fadeInOut(opts, value) |> snd
      );
  };
};
