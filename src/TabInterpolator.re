open BsReactNative;

type interpolator = Animated.Value.t => Style.t;

type t = {forCard: interpolator};

let default = {
  forCard: value => {
    let screenWidth = float_of_int(Dimensions.get(`window)##width);
    Style.(
      style([
        Transform.makeInterpolated(
          ~translateX=
            Animated.Value.interpolate(
              value,
              ~inputRange=[(-1), 0, 1] |> List.map(float),
              ~outputRange=`float([-. screenWidth, 0.0, screenWidth]),
              (),
            ),
          (),
        ),
      ])
    );
  },
};