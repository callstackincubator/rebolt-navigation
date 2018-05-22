module PanHandler = {
  [@bs.module "react-native-gesture-handler"]
  external view : ReasonReact.reactClass = "PanGestureHandler";
  let make =
      (
        ~onGestureEvent,
        ~maxDeltaX,
        ~enabled,
        ~onHandlerStateChange,
        ~minDeltaX,
        ~hitSlop,
        children,
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=view,
      ~props={
        "onGestureEvent": onGestureEvent,
        "onHandlerStateChange": onHandlerStateChange,
        "maxDeltaX": maxDeltaX,
        "minDeltaX": minDeltaX,
        "enabled": enabled,
        "hitSlop": hitSlop,
      },
      children,
    );
};