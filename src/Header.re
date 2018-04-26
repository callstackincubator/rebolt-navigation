open BsReactNative;

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
  type state = {widths: Utils.IntMap.t(float)};
  type action =
    | SetWidth(int, float);
  let component = ReasonReact.reducerComponent("FloatingHeader");
  let make = (~headerProps as props: props, _children) => {
    ...component,
    initialState: () => {widths: Utils.IntMap.empty},
    reducer: (action, state) =>
      switch (action) {
      | SetWidth(idx, width) =>
        ReasonReact.Update({
          widths: state.widths |> Utils.IntMap.add(idx, width)
        })
      },
    render: self => {
      let {screens, activeScreen, animatedValue as anim, pop} = props;
      /**
       * The animated value passed to Header is screen index -
       * gesture progress. When user starts moving its finger
       * on initial screen, this value can get negative. We do the
       * following interpolation to guard against such invalid state.
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
      let renderLeft = ({screens, animatedValue, activeScreen as idx}) =>
        <Animated.View
          style=(
            Style.concat([
              Styles.left,
              animatedValue
              |> screens[idx].animation.forHeaderLeft({idx: idx}),
            ])
          )>
          (
            idx === 0 ?
              <View /> :
              <TouchableOpacity onPress=(_e => pop(screens[idx].key))>
                <View style=Styles.leftContainer>
                  <Animated.View
                    style=(
                      animatedValue
                      |> screens[idx].animation.forHeaderLeftButton({
                           idx: idx,
                         })
                    )>
                    <Image
                      style=(
                        Styles.leftIcon(
                          Js.Option.isSome(screens[idx].header.title),
                        )
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
                    | Some(title) =>
                      <Animated.View
                        style=(
                          animatedValue
                          |> screens[idx].animation.forHeaderLeftLabel({
                               idx: idx,
                             })
                        )>
                        <Text style=Styles.leftTitle numberOfLines=1>
                          (ReasonReact.stringToElement(title))
                        </Text>
                      </Animated.View>
                    }
                  )
                </View>
              </TouchableOpacity>
          )
        </Animated.View>;
      let renderTitle = ({screens, animatedValue, activeScreen as idx}) =>
        <Animated.View
          style=(
            Style.concat([
              Styles.center,
              animatedValue
              |> screens[idx].animation.forHeaderCenter({idx: idx}),
            ])
          )>
          <Text
            onLayout=(
              e =>
                self.send(
                  SetWidth(idx, RNEvent.NativeLayoutEvent.layout(e).width),
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
              animatedValue
              |> screens[idx].animation.forHeaderRight({idx: idx}),
            ])
          )
        />;
      <SafeAreaView style=Styles.container>
        <View style=Styles.header>
          Js.Option.(
            screens
            |> Array.mapi((idx: int, screen) => {
                 let props = {
                   ...props,
                   animatedValue: anim,
                   activeScreen: idx,
                 };
                 <MaskedView
                   key=(string_of_int(idx))
                   maskElement=mask
                   style=Styles.fill
                   pointerEvents=(activeScreen == idx ? "box-none" : "none")>
                   (
                     (screen.header.renderLeft |> getWithDefault(renderLeft))(
                       props,
                     )
                   )
                   (
                     (screen.header.renderTitle |> getWithDefault(renderTitle))(
                       props,
                     )
                   )
                   (
                     (screen.header.renderRight |> getWithDefault(renderRight))(
                       props,
                     )
                   )
                 </MaskedView>;
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