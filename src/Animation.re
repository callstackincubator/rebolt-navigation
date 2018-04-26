open BsReactNative;

type interpolator = Animated.Value.t => Style.t;

type t = {
  func:
    (
      ~value: Animated.Value.value,
      ~toValue: [ | `animated(Animated.Value.value) | `raw(float)]
    ) =>
    Animated.CompositeAnimation.t,
  forCard: interpolator,
  forHeaderCenter: interpolator,
  forHeaderLeft: interpolator,
  forHeaderLeftLabel: interpolator,
  forHeaderLeftButton: interpolator,
  forHeaderRight: interpolator,
};

let crossFadeInterpolation = ([start, mid, end_], value) =>
  Animated.Value.interpolate(
    value,
    ~inputRange=[
      start,
      start +. 0.001,
      mid -. 0.9,
      mid -. 0.2,
      mid,
      end_ -. 0.001,
      end_,
    ],
    ~outputRange=`float([0.0, 0.0, 0.0, 0.3, 1.0, 0.0, 0.0]),
    (),
  );

let slideHorizontal = {
  func:
    Animated.Spring.animate(
      ~stiffness=1000.0,
      ~damping=500.0,
      ~mass=3.0,
      ~useNativeDriver=Js.Boolean.to_js_boolean(true),
      (),
    ),
  forCard: value => {
    let screenWidth = float(Dimensions.get(`window)##width);
    Style.(
      style([
        opacity(
          Interpolated(
            Animated.Value.interpolate(
              value,
              ~inputRange=[(-1.0), (-0.99), 0.0, 0.99, 1.0],
              ~outputRange=`float([0.0, 1.0, 1.0, 0.85, 0.0]),
              (),
            ),
          ),
        ),
        Transform.makeInterpolated(
          ~translateX=
            Animated.Value.interpolate(
              value,
              ~inputRange=[(-1), 0, 1] |> List.map(float),
              ~outputRange=`float([-. screenWidth *. 0.3, 0.0, screenWidth]),
              (),
            ),
          (),
        ),
      ])
    );
  },
  forHeaderCenter: value => {
    let offset = float_of_int(Dimensions.get(`window)##width / 2 - 70 + 25);
    Style.(
      style([
        opacity(
          Interpolated(
            Animated.Value.interpolate(
              value,
              ~inputRange=[(-1.0), (-0.999), (-0.5), 0.0, 0.7, 0.999, 1.0],
              ~outputRange=`float([0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0]),
              (),
            ),
          ),
        ),
        Transform.makeInterpolated(
          ~translateX=
            Animated.Value.interpolate(
              value,
              ~inputRange=[(-1.0), (-0.99), 0.0, 0.99, 1.0],
              ~outputRange=
                `float([offset, offset, 0.0, -. offset, -. offset]),
              (),
            ),
          (),
        ),
      ])
    );
  },
  /*** Not used on iOS */
  forHeaderLeft: _value => Style.style([]),
  forHeaderLeftButton: value =>
    Style.(
      style([
        opacity(
          Interpolated(
            Animated.Value.interpolate(
              value,
              ~inputRange=[(-1.0), (-0.999), (-0.5), 0.0, 0.5, 0.999, 1.0],
              ~outputRange=`float([0.0, 0.0, 0.7, 1.0, 0.7, 0.0, 0.0]),
              (),
            ),
          ),
        ),
      ])
    ),
  forHeaderLeftLabel: value => {
    let offset = float_of_int(Dimensions.get(`window)##width / 2 - 70 + 25);
    Style.(
      style([
        opacity(
          Interpolated(
            Animated.Value.interpolate(
              value,
              ~inputRange=[(-1.0), (-0.999), (-0.35), 0.0, 0.5, 0.999, 1.0],
              ~outputRange=`float([0.0, 0.0, 0.0, 1.0, 0.5, 0.0, 0.0]),
              (),
            ),
          ),
        ),
        Transform.makeInterpolated(
          ~translateX=
            Animated.Value.interpolate(
              value,
              ~inputRange=[(-1.0), (-0.999), 0.0, 0.999, 1.0],
              ~outputRange=
                `float([
                  offset,
                  offset,
                  0.0,
                  -. offset *. 1.5,
                  -. offset *. 1.5,
                ]),
              (),
            ),
          (),
        ),
      ])
    );
  },
  forHeaderRight: value =>
    Style.(
      style([
        opacity(
          Interpolated(value |> crossFadeInterpolation([(-1.0), 0.0, 1.0])),
        ),
      ])
    ),
};

let fadeVertical = {
  func:
    Animated.Timing.animate(
      ~duration=350.0,
      ~easing=t => Js.Math.pow_float(t, 5.0),
      ~useNativeDriver=Js.Boolean.to_js_boolean(true),
      (),
    ),
  forCard: value =>
    Style.(
      style([
        opacity(
          Interpolated(
            Animated.Value.interpolate(
              value,
              ~inputRange=[(-1.0), (-0.99), 0.0, 1.0],
              ~outputRange=`float([0.0, 1.0, 1.0, 0.0]),
              (),
            ),
          ),
        ),
        Transform.makeInterpolated(
          ~translateY=
            Animated.Value.interpolate(
              value,
              ~inputRange=[(-1.0), (-0.99), 0.0, 1.0],
              ~outputRange=`float([0.0, 0.0, 0.0, 50.0]),
              (),
            ),
          (),
        ),
      ])
    ),
  forHeaderCenter: (_) => Style.style([]),
  forHeaderLeft: (_) => Style.style([]),
  forHeaderLeftLabel: (_) => Style.style([]),
  forHeaderLeftButton: (_) => Style.style([]),
  forHeaderRight: (_) => Style.style([]),
};

let default =
  switch (Platform.os()) {
  | Platform.Android => fadeVertical
  | _ => slideHorizontal
  };

let none = {
  ...default,
  func:
    Animated.Timing.animate(
      ~duration=0.0,
      ~useNativeDriver=Js.Boolean.to_js_boolean(true),
      (),
    ),
};