type config = {title: option(string)};

type screenConfig = {
  header: config,
  animation: Animation.t,
  key: string
};

let default: config;

module FloatingHeader: {
  module Styles: {
    module Constants: {
      let titleOffset: float;
      let appBarHeight: float;
      let statusBarHeight: float;
    };
    let container: BsReactNative.Style.t;
    let header: BsReactNative.Style.t;
    let fill: BsReactNative.Style.t;
    let center: BsReactNative.Style.t;
    let headerTitle: BsReactNative.Style.t;
    let left: BsReactNative.Style.t;
    let leftTitle: BsReactNative.Style.t;
    let leftContainer: BsReactNative.Style.t;
    let leftIcon: bool => BsReactNative.Style.t;
    let iconMaskContainer: BsReactNative.Style.t;
    let iconMask: BsReactNative.Style.t;
    let iconMaskFillerRect: BsReactNative.Style.t;
    let right: BsReactNative.Style.t;
    let label: BsReactNative.Style.t;
  };
  let component:
    ReasonReact.componentSpec(
      ReasonReact.stateless,
      ReasonReact.stateless,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      ReasonReact.actionless
    );
  let make:
    (
      ~screens: array(screenConfig),
      ~activeScreen: int,
      ~animatedValue: BsReactNative.Animated.Value.t,
      ~pop: string => unit,
      'a
    ) =>
    ReasonReact.componentSpec(
      ReasonReact.stateless,
      ReasonReact.stateless,
      ReasonReact.noRetainedProps,
      ReasonReact.noRetainedProps,
      ReasonReact.actionless
    );
};

module PlatformHeader = FloatingHeader;