open BsReactNative;

type options = {idx: int};

/**
 * Interpolates style
 */
type interpolator = (options, Animated.Value.t) => Style.t;

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
      ~value: Animated.Value.value,
      ~toValue: [ | `animated(Animated.Value.value) | `raw(float)]
    ) =>
    Animated.CompositeAnimation.t,
  forCard: interpolator,
  forHeaderCenter: interpolator,
  forHeaderLeft: interpolator,
  forHeaderLeftLabel: interpolator,
  forHeaderRight: interpolator
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
      end_
    ],
    ~outputRange=`float([0.0, 0.0, 0.0, 0.3, 1.0, 0.0, 0.0]),
    ()
  );

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
              ~outputRange=`float([-. screenWidth *. 0.3, 0.0, screenWidth]),
              ()
            ),
          ()
        )
      ])
    );
  },
  forHeaderCenter: ({idx}, value) => {
    let offset = float_of_int(Dimensions.get(`window)##width / 2 - 70 + 25);
    let index = float_of_int(idx);
    let (first, last) = (index -. 1.0, index +. 1.0);
    Style.(
      style([
        opacity(
          Interpolated(
            Animated.Value.interpolate(
              value,
              ~inputRange=[
                first,
                first +. 0.001,
                index -. 0.5,
                index,
                index +. 0.7,
                last -. 0.001,
                last
              ],
              ~outputRange=`float([0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 0.0]),
              ()
            )
          )
        ),
        Transform.makeInterpolated(
          ~translateX=
            Animated.Value.interpolate(
              value,
              ~inputRange=[first, first +. 0.001, index, last -. 0.001, last],
              ~outputRange=`float([offset, offset, 0.0, -. offset, -. offset]),
              ()
            ),
          ()
        )
      ])
    );
  },
  /*** Not used on iOS */
  forHeaderLeft: (_opts, _value) => Style.style([]),
  forHeaderLeftLabel: ({idx}, value) => {
    let offset = float_of_int(Dimensions.get(`window)##width / 2 - 70 + 25);
    let index = float_of_int(idx);
    let (first, last) = (index -. 1.0, index +. 1.0);
    Style.(
      style([
        opacity(
          Interpolated(
            Animated.Value.interpolate(
              value,
              ~inputRange=[
                first,
                first +. 0.001,
                index -. 0.35,
                index,
                index +. 0.5,
                last -. 0.001,
                last
              ],
              ~outputRange=`float([0.0, 0.0, 0.0, 1.0, 0.5, 0.0, 0.0]),
              ()
            )
          )
        ),
        Transform.makeInterpolated(
          ~translateX=
            Animated.Value.interpolate(
              value,
              ~inputRange=[first, first +. 0.001, index, last -. 0.001, last],
              ~outputRange=
                `float([
                  offset,
                  offset,
                  0.0,
                  -. offset *. 1.5,
                  -. offset *. 1.5
                ]),
              ()
            ),
          ()
        )
      ])
    );
  },
  forHeaderRight: ({idx}, value) => {
    let index = float_of_int(idx);
    Style.(
      style([
        opacity(
          Interpolated(
            value
            |> crossFadeInterpolation([index -. 1.0, index, index +. 1.0])
          )
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
  forCard: (_options, _value) => Style.style([]),
  forHeaderLeft: (_opts, _value) => Style.style([]),
  forHeaderLeftLabel: (_opts, _value) => Style.style([]),
  forHeaderRight: (_opts, _value) => Style.style([]),
  forHeaderCenter: (_opts, _value) => Style.style([])
};