type interpolator = Rebolt.Animated.Value.t => Rebolt.Style.t;

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