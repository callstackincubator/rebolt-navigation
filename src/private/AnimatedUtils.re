open BsReactNative.Animated;


/***
 * Built-in Animated doesn't allow for interpolated Animated.Values
 * to be combined with other non-interpolated Values (e.g. `add`).
 *
 * This module provides `interpolate` that returns Animated.Value.t instead.
 *
 * Be aware that this is unsafe since interpolated values are a bit different
 * than regular ones.
 */
type config;

type outputRange;

[@bs.obj]
external makeConfig :
  (
    ~inputRange: array(float),
    ~outputRange: outputRange,
    ~easing: Easing.t=?,
    ~extrapolate: string=?,
    ~extrapolateLeft: string=?,
    ~extrapolateRight: string=?
  ) =>
  config =
  "";

external outputRangeCreate : 'a => outputRange = "%identity";

let extrapolateString = x =>
  switch (x) {
  | Interpolation.Extend => "extend"
  | Interpolation.Clamp => "clamp"
  | Interpolation.Identity => "identity"
  };

[@bs.send]
external _interpolate : (Value.t, config) => Value.t = "interpolate";

let interpolate =
    (
      value,
      ~inputRange,
      ~outputRange,
      ~easing=?,
      ~extrapolate=?,
      ~extrapolateLeft=?,
      ~extrapolateRight=?,
      (),
    ) =>
  _interpolate(
    value,
    makeConfig(
      ~inputRange=Array.of_list(inputRange),
      ~outputRange=
        switch (outputRange) {
        | `string((x: list(string))) => outputRangeCreate(Array.of_list(x))
        | `float((x: list(float))) => outputRangeCreate(Array.of_list(x))
        },
      ~easing?,
      ~extrapolate=?Utils.option_map(extrapolateString, extrapolate),
      ~extrapolateLeft=?Utils.option_map(extrapolateString, extrapolateLeft),
      ~extrapolateRight=?
        Utils.option_map(extrapolateString, extrapolateRight),
    ),
  );