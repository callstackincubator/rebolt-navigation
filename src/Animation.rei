type options = {idx: int};

type interpolator =
  (options, BsReactNative.Animated.Value.t) => BsReactNative.Style.t;

type t = {
  func:
    (
      ~value: BsReactNative.Animated.Value.value,
      ~toValue: [
                  | `animated(BsReactNative.Animated.Value.value)
                  | `raw(float)
                ]
    ) =>
    BsReactNative.Animated.CompositeAnimation.t,
  forCard: interpolator,
  forHeaderCenter: interpolator,
  forHeaderLeft: interpolator,
  forHeaderLeftLabel: interpolator,
  forHeaderLeftButton: interpolator,
  forHeaderRight: interpolator
};

let slideInOut: t;

let default: t;

let none: t;