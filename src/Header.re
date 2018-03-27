open BsReactNative;

/**
 * Header config
 */
type config = {title: option(string)};

/**
 * Screen config that is used by this Header
 */
type screenConfig = {
  header: config,
  animation: Animation.t
};

/**
 * Default configuration used on Screen that is mounting or has
 * no Screen component inside
 */
let default = {title: None};

/**
 * Default implementation of Header on iOS
 */
module FloatingHeader = {
  module Styles = {
    open Style;
    module Constants = {
      let titleOffset = 70.0;
      let appBarHeight = 44.0;
      let statusBarHeight = 20.0;
    };
    let container =
      style([
        backgroundColor(String("#FFF")),
        height(Pt(Constants.(appBarHeight +. statusBarHeight))),
        borderBottomWidth(StyleSheet.hairlineWidth),
        borderBottomColor(String("#A7A7AA"))
      ]);
    let header =
      style([
        flex(1.0),
        position(Relative),
        /*
         * SafeAreaView doesn't work on iOS < 11 and so, we add the
         * statusBar padding manually
         */
        marginTop(
          Pt(Platform.version() < 11 ? Constants.statusBarHeight : 0.0)
        )
      ]);
    let flex = StyleSheet.absoluteFill;
    let center =
      style([
        bottom(Pt(0.0)),
        top(Pt(0.0)),
        left(Pt(Constants.titleOffset)),
        right(Pt(Constants.titleOffset)),
        position(Absolute),
        flexDirection(Row),
        justifyContent(Center),
        alignItems(Center)
      ]);
    let headerTitle =
      style([
        fontSize(Float(17.0)),
        fontWeight(`_700),
        textAlign(Center),
        marginHorizontal(Pt(16.0)),
        color(String("rgba(0, 0, 0, .9)"))
      ]);
    let left =
      style([
        left(Pt(0.0)),
        top(Pt(0.0)),
        bottom(Pt(0.0)),
        position(Absolute),
        flexDirection(Row),
        alignItems(Center)
      ]);
    let leftTitle = style([fontSize(Float(17.0)), color(String("#037aff"))]);
    let leftContainer = style([flexDirection(Row), alignItems(Center)]);
    let leftIcon = withTitle =>
      style([
        height(Pt(21.0)),
        width(Pt(12.0)),
        marginLeft(Pt(9.0)),
        marginRight(Pt(withTitle ? 3.0 : 22.0)),
        marginVertical(Pt(12.0)),
        resizeMode(Contain)
      ]);
    let right =
      style([
        right(Pt(0.0)),
        top(Pt(0.0)),
        bottom(Pt(0.0)),
        position(Absolute),
        flexDirection(Row),
        alignItems(Center)
      ]);
    let label = style([fontSize(Float(15.0)), color(String("red"))]);
  };
  let renderLeft = header =>
    <View style=Styles.left>
      <TouchableOpacity>
        <View style=Styles.leftContainer>
          <Image
            style=(Styles.leftIcon(Js.Option.isSome(header.title)))
            source=(
              Required(Packager.require("../../../src/assets/back-icon.png"))
            )
          />
          (
            switch header.title {
            | None => <View />
            | Some(title) =>
              <Text style=Styles.leftTitle numberOfLines=1>
                (ReasonReact.stringToElement(title))
              </Text>
            }
          )
        </View>
      </TouchableOpacity>
    </View>;
  let renderRight = _header => <View style=Styles.right />;
  let component = ReasonReact.statelessComponent("FloatingHeader");
  let make =
      (
        ~screens: array(screenConfig),
        ~animatedValue as anim: Animated.Value.t,
        _children
      ) => {
    ...component,
    render: _self =>
      <SafeAreaView style=Styles.container>
        <View style=Styles.header>
          (
            screens
            |> Array.mapi((idx: int, screen) =>
                 <View key=(string_of_int(idx)) style=Styles.flex>
                   (idx > 0 ? renderLeft(screens[idx - 1].header) : <View />)
                   <Animated.View
                     style=(
                       Style.concat([
                         Styles.center,
                         anim |> screen.animation.forHeaderCenter({idx: idx})
                       ])
                     )>
                     <Text style=Styles.headerTitle numberOfLines=1>
                       (
                         ReasonReact.stringToElement(
                           Js.Option.getWithDefault("", screen.header.title)
                         )
                       )
                     </Text>
                   </Animated.View>
                   (renderRight(screen.header))
                 </View>
               )
            |> ReasonReact.arrayToElement
          )
        </View>
      </SafeAreaView>
  };
};

module PlatformHeader = FloatingHeader;