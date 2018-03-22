open BsReactNative;

/**
 * Header config
 */
type config = {title: option(string)};

/**
 * Screen config that is used by this Header
 */
type screenConfig = {header: config};

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
        backgroundColor("#FFF"),
        height(Pt(Constants.(appBarHeight +. statusBarHeight))),
        position(Relative)
      ]);
    let header =
      concat([StyleSheet.absoluteFill, style([flexDirection(Row)])]);
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
        color("rgba(0, 0, 0, .9)")
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
    let right =
      style([
        right(Pt(0.0)),
        top(Pt(0.0)),
        bottom(Pt(0.0)),
        position(Absolute),
        flexDirection(Row),
        alignItems(Center)
      ]);
    let label = style([fontSize(Float(15.0)), color("red")]);
  };
  let renderLeft = _header => <View style=Styles.left />;
  let renderRight = _header => <View style=Styles.right />;
  let renderCenter = header =>
    <View style=Styles.center>
      <Text style=Styles.headerTitle numberOfLines=1>
        (
          ReasonReact.stringToElement(
            Js.Option.getWithDefault("", header.title)
          )
        )
      </Text>
    </View>;
  let component = ReasonReact.statelessComponent("FloatingHeader");
  let make = (~screens: array(screenConfig), _children) => {
    ...component,
    render: _self =>
      <View style=Styles.container>
        (
          screens
          |> Array.mapi((idx: int, {header}) =>
               <View key=(string_of_int(idx)) style=Styles.header>
                 (idx > 1 ? renderLeft(screens[idx - 1].header) : <View />)
                 (renderCenter(header))
                 (renderRight(header))
               </View>
             )
          |> ReasonReact.arrayToElement
        )
      </View>
  };
};