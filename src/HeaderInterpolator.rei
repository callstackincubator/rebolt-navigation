type interpolator = BsReactNative.Animated.Value.t => BsReactNative.Style.t;

type t = {
  forHeaderCenter: interpolator,
  forHeaderLeft: interpolator,
  forHeaderLeftLabel: interpolator,
  forHeaderLeftButton: interpolator,
  forHeaderRight: interpolator,
};

/**
 * Floating interpolation used for Header on iOS
 */
let floating: t;