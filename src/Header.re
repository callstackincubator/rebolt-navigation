open BsReactNative;

open Utils;

type config = {
  title: option(string),
  style: option(BsReactNative.Style.t),
  renderTitle: option(returnsComponent),
  renderLeft: option(returnsComponent),
  renderRight: option(returnsComponent),
}
and returnsComponent = props => ReasonReact.reactElement
and screen = {
  header: config,
  animation: Animation.t,
  key: string,
}
and props = {
  screens: array(screen),
  activeScreen: int,
  animatedValue: Animated.Value.t,
  pop: string => unit,
};

let default = {
  title: None,
  style: None,
  renderTitle: None,
  renderLeft: None,
  renderRight: None,
};

/**
 * Bare minimum wrapper around MaskedViewIOS. Consider open sourcing to
 * `bs-react-native` at some point
 */
module MaskedView = {
  [@bs.module "react-native"]
  external view : ReasonReact.reactClass = "MaskedViewIOS";
  let make = (~maskElement, ~pointerEvents, ~style, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=view,
      ~props={
        "maskElement": maskElement,
        "pointerEvents": pointerEvents,
        "style": style,
      },
      children,
    );
};

module TouchableNativeFeedback = {
  module Background = {
    type t;
    [@bs.module "react-native"] [@bs.scope "TouchableNativeFeedback"]
    external ripple_ : (string, Js.boolean) => t = "Ripple";
    let ripple = (color, borderless) =>
      ripple_(color, Js.Boolean.to_js_boolean(borderless));
  };
  [@bs.module "react-native"]
  external view : ReasonReact.reactClass = "TouchableNativeFeedback";
  let make =
      (~onPress=?, ~style=?, ~background: option(Background.t)=?, children) =>
    Js.Undefined.(
      ReasonReact.wrapJsForReason(
        ~reactClass=view,
        ~props={
          "onPress": fromOption(onPress),
          "background": fromOption(background),
          "style": fromOption(style),
        },
        <View> ...children </View>,
      )
    );
};

/**
 * Wrapper around `TouchableNativeFeedback` that makes sure Ripple effect
 * is used on Android devices that support this version.
 */
module TouchableItem = {
  let component = ReasonReact.statelessComponent("TouchableItem");
  let make =
      (
        ~pressColor="rgba(0, 0, 0, .32)",
        ~onPress=() => (),
        ~borderless=true,
        children,
      ) => {
    ...component,
    render: _self =>
      Platform.version() >= 21 && Platform.os() == Platform.Android ?
        <TouchableNativeFeedback
          onPress
          background=(
            TouchableNativeFeedback.Background.ripple(pressColor, borderless)
          )>
          ...children
        </TouchableNativeFeedback> :
        <TouchableOpacity onPress> ...children </TouchableOpacity>,
  };
};

module IOSImpl = {
  module Styles = {
    open Style;
    module Constants = {
      let titleOffset = 70.0;
      let appBarHeight = 44.0;
      let statusBarHeight = 20.0;
    };
    let container =
      style([
        backgroundColor(String("#fff")),
        borderBottomWidth(StyleSheet.hairlineWidth),
        borderBottomColor(String("#A7A7AA")),
      ]);
    let header =
      style([
        height(Pt(Constants.(appBarHeight))),
        position(Relative),
        /*
         * SafeAreaView doesn't work on iOS < 11 and so, we add the
         * statusBar padding manually
         */
        marginTop(
          Pt(Platform.version() < 11 ? Constants.statusBarHeight : 0.0),
        ),
      ]);
    let fill = StyleSheet.absoluteFill;
    let center =
      style([
        bottom(Pt(0.0)),
        top(Pt(0.0)),
        left(Pt(Constants.titleOffset)),
        right(Pt(Constants.titleOffset)),
        position(Absolute),
        flexDirection(Row),
        justifyContent(Center),
        alignItems(Center),
      ]);
    let headerTitle =
      style([
        fontSize(Float(17.0)),
        fontWeight(`_700),
        textAlign(Center),
        marginHorizontal(Pt(16.0)),
        color(String("rgba(0, 0, 0, .9)")),
      ]);
    let left =
      style([
        left(Pt(0.0)),
        top(Pt(0.0)),
        bottom(Pt(0.0)),
        position(Absolute),
        flexDirection(Row),
        alignItems(Center),
      ]);
    let leftTitle =
      style([fontSize(Float(17.0)), color(String("#037aff"))]);
    let leftContainer = style([flexDirection(Row), alignItems(Center)]);
    let leftIcon = withTitle =>
      style([
        height(Pt(21.0)),
        width(Pt(12.0)),
        marginLeft(Pt(9.0)),
        marginRight(Pt(withTitle ? 3.0 : 22.0)),
        marginVertical(Pt(12.0)),
        resizeMode(Contain),
      ]);
    let iconMaskContainer =
      style([flex(1.0), flexDirection(Row), justifyContent(Center)]);
    let iconMask =
      style([
        height(Pt(21.0)),
        width(Pt(12.0)),
        marginLeft(Pt(9.0)),
        marginTop(Pt(-0.5)),
        alignSelf(Center),
        resizeMode(Contain),
      ]);
    let iconMaskFillerRect =
      style([
        flex(1.0),
        backgroundColor(String("#d8d8d8")),
        marginLeft(Pt(-1.0)),
      ]);
    let right =
      style([
        right(Pt(0.0)),
        top(Pt(0.0)),
        bottom(Pt(0.0)),
        position(Absolute),
        flexDirection(Row),
        alignItems(Center),
      ]);
  };
  /**
   * In order to be able to render `BackButton` correctly, we measure the
   * title and left container areas on each render and store the widths
   * in state.
   *
   * We use it to decide whether back button should be rendered at its full width
   * vs `Back`.
   */
  type state = {
    titleWidths: StringMap.t(float),
    leftWidths: StringMap.t(float),
  };
  type action =
    | SetTitleWidth(string, float)
    | SetLeftWidth(string, float);
  let component = ReasonReact.reducerComponent("FloatingHeader");
  let make = (~headerProps as props: props, _children) => {
    ...component,
    initialState: () => {
      titleWidths: StringMap.empty,
      leftWidths: StringMap.empty,
    },
    reducer: (action, state) =>
      switch (action) {
      | SetTitleWidth(key, width) =>
        ReasonReact.Update({
          ...state,
          titleWidths: state.titleWidths |> StringMap.add(key, width),
        })
      | SetLeftWidth(key, width) =>
        ReasonReact.Update({
          ...state,
          leftWidths: state.leftWidths |> StringMap.add(key, width),
        })
      },
    render: self => {
      let {screens, activeScreen, animatedValue as anim, pop} = props;
      /**
       * The animated value passed to Header is screen index -
       * gesture progress. When user starts moving its finger
       * on initial screen, this value can get negative. We do the
       * following interpolation to guard against such invalid state.
       *
       * Note: Animated seems to be not working properly when inputRange
       * starts and ends with the same number (0, 0). This can happen
       * when there's only a single route on the stack. To prevent that,
       * we make it lastIndex + 1.
       */
      let upperBound = float_of_int(Array.length(screens));
      let anim =
        AnimatedUtils.interpolate(
          anim,
          ~inputRange=[0.0, upperBound],
          ~outputRange=`float([0.0, upperBound]),
          ~extrapolate=Animated.Interpolation.Clamp,
          (),
        );
      let mask =
        <View style=Styles.iconMaskContainer>
          <Image
            source=(
              Required(
                Packager.require("../../../src/assets/back-icon-mask.png"),
              )
            )
            style=Styles.iconMask
          />
          <View style=Styles.iconMaskFillerRect />
        </View>;
      let renderLeft = ({screens, animatedValue, activeScreen as idx}) => {
        let scr = screens[idx];
        <Animated.View
          style=Style.(
                  concat([
                    Styles.left,
                    animatedValue |> scr.animation.forHeaderLeft,
                  ])
                )>
          (
            idx === 0 ?
              <View /> :
              <TouchableOpacity onPress=(_e => pop(scr.key))>
                <View
                  onLayout=(
                    /**
                     * We are interested in measuring the left container
                     * only once to prevent infinite loops.
                     */
                    self.state.leftWidths
                    |> StringMap.hasKey(scr.key) ?
                      e_ => () :
                      (
                        e =>
                          self.send(
                            SetLeftWidth(
                              scr.key,
                              RNEvent.NativeLayoutEvent.layout(e).width,
                            ),
                          )
                      )
                  )
                  style=Styles.leftContainer>
                  <Animated.View
                    style=(animatedValue |> scr.animation.forHeaderLeftButton)>
                    <Image
                      style=(
                        Styles.leftIcon(Js.Option.isSome(scr.header.title))
                      )
                      source=(
                        Required(
                          Packager.require(
                            "../../../src/assets/back-icon.png",
                          ),
                        )
                      )
                    />
                  </Animated.View>
                  (
                    switch (screens[idx - 1].header.title) {
                    | None => <View />
                    | Some(backTitle) =>
                      <Animated.View
                        style=(
                          animatedValue |> scr.animation.forHeaderLeftLabel
                        )>
                        <Text
                          style=Style.(
                                  concat([
                                    Styles.leftTitle,
                                    style([
                                      opacity(
                                        Float(
                                          self.state.leftWidths
                                          |> StringMap.hasKey(scr.key)
                                          && self.state.titleWidths
                                          |> StringMap.hasKey(scr.key) ?
                                            1.0 : 0.0,
                                        ),
                                      ),
                                    ]),
                                  ])
                                )
                          numberOfLines=1>
                          (
                            ReasonReact.stringToElement(
                              /**
                               * Measure the space left for the back button and decide
                               * whether to print "Back" or the original back button,
                               * which is title of the previous scene.
                               */
                              (
                                try (
                                  {
                                    let lw =
                                      self.state.leftWidths
                                      |> StringMap.find(scr.key);
                                    let tw =
                                      self.state.titleWidths
                                      |> StringMap.find(scr.key);
                                    let ww =
                                      Dimensions.get(`window)##width
                                      |> float_of_int;
                                    lw +. 20.0 >= (ww -. tw) /. 2.0 ?
                                      "Back" : backTitle;
                                  }
                                ) {
                                | Not_found => backTitle
                                }
                              ),
                            )
                          )
                        </Text>
                      </Animated.View>
                    }
                  )
                </View>
              </TouchableOpacity>
          )
        </Animated.View>;
      };
      let renderTitle = ({screens, animatedValue, activeScreen as idx}) =>
        <Animated.View
          style=(
            Style.concat([
              Styles.center,
              animatedValue |> screens[idx].animation.forHeaderCenter,
            ])
          )>
          <Text
            onLayout=(
              e =>
                self.send(
                  SetTitleWidth(
                    screens[idx].key,
                    RNEvent.NativeLayoutEvent.layout(e).width,
                  ),
                )
            )
            style=Styles.headerTitle
            numberOfLines=1>
            (
              ReasonReact.stringToElement(
                Js.Option.getWithDefault("", screens[idx].header.title),
              )
            )
          </Text>
        </Animated.View>;
      let renderRight = ({screens, animatedValue, activeScreen as idx}) =>
        <Animated.View
          style=(
            Style.concat([
              Styles.right,
              animatedValue |> screens[idx].animation.forHeaderRight,
            ])
          )
        />;
      let lastIdx = Array.length(screens) - 1;
      <SafeAreaView style=Styles.container>
        <View style=Styles.header>
          Js.Option.(
            screens
            |> Array.mapi((idx: int, screen) => {
                 let props = {
                   ...props,
                   animatedValue:
                     Animated.Value.add(
                       anim,
                       Animated.Value.create(-. float_of_int(idx)),
                     ),
                   activeScreen: idx,
                 };
                 /* Render a header for two last routes to improve performance */
                 if (lastIdx - idx > 1) {
                   <View key=(string_of_int(idx)) />;
                 } else {
                   <MaskedView
                     key=(string_of_int(idx))
                     maskElement=mask
                     style=Styles.fill
                     pointerEvents=(activeScreen == idx ? "box-none" : "none")>
                     (
                       (
                         screen.header.renderTitle
                         |> getWithDefault(renderTitle)
                       )(
                         props,
                       )
                     )
                     (
                       (screen.header.renderLeft |> getWithDefault(renderLeft))(
                         props,
                       )
                     )
                     (
                       (
                         screen.header.renderRight
                         |> getWithDefault(renderRight)
                       )(
                         props,
                       )
                     )
                   </MaskedView>;
                 };
               })
            |> ReasonReact.arrayToElement
          )
        </View>
      </SafeAreaView>;
    },
  };
};

module IOS = {
  let component = ReasonReact.statelessComponent("IOSHeader");
  let make = (~headerProps as p: props, _children) => {
    ...component,
    render: _self => <IOSImpl headerProps=p />,
  };
};

module Android = {
  module Styles = {
    open Style;
    let header =
      style([
        backgroundColor(String("#FFF")),
        shadowColor(String("black")),
        shadowOpacity(0.1),
        shadowRadius(StyleSheet.hairlineWidth),
        shadowOffset(~width=0.0, ~height=StyleSheet.hairlineWidth),
        elevation(4.0),
        height(Pt(56.0)),
        alignItems(Center),
        flexDirection(Row),
      ]);
    let title =
      style([
        justifyContent(FlexStart),
        fontSize(Float(20.0)),
        fontWeight(`_500),
        color(String("rgba(0, 0, 0, 0.9)")),
        marginHorizontal(Pt(16.0)),
      ]);
    let icon =
      style([
        height(Pt(24.0)),
        width(Pt(24.0)),
        margin(Pt(16.0)),
        marginRight(Pt(0.0)),
        resizeMode(Contain),
      ]);
  };
  let component = ReasonReact.statelessComponent("AndroidHeader");
  let renderTitle = ({screens, activeScreen as i}) =>
    <Text style=Styles.title>
      (
        ReasonReact.stringToElement(
          Js.Option.getWithDefault("", screens[i].header.title),
        )
      )
    </Text>;
  let renderLeft = ({screens, activeScreen as i, pop}) =>
    i > 0 ?
      <TouchableItem onPress=(_e => pop(screens[i].key))>
        <Image
          style=Styles.icon
          source=(
            Required(Packager.require("../../../src/assets/back-icon.png"))
          )
        />
      </TouchableItem> :
      <View />;
  let renderRight = _props => <View />;
  let make = (~headerProps as p: props, _children) => {
    ...component,
    render: _self => {
      let header = p.screens[p.activeScreen].header;
      Js.Option.(
        <View
          style=Style.(
                  concat([
                    Styles.header,
                    header.style |> getWithDefault(style([])),
                  ])
                )>
          ((header.renderLeft |> getWithDefault(renderLeft))(p))
          ((header.renderTitle |> getWithDefault(renderTitle))(p))
          ((header.renderRight |> getWithDefault(renderRight))(p))
        </View>
      );
    },
  };
};