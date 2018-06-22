open Rebolt;

type t = {
  forHeaderCenter: 'a .Animated.value('a) => Style.t,
  forHeaderLeft: 'a .Animated.value('a) => Style.t,
  forHeaderLeftLabel: 'a .Animated.value('a) => Style.t,
  forHeaderLeftButton: 'a .Animated.value('a) => Style.t,
  forHeaderRight: 'a .Animated.value('a) => Style.t,
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

let floating = {
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