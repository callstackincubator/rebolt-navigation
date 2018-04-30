open BsReactNative;

open Navigation;

module Styles = {
  open Style;
  let tabBar =
    style([
      flex(1.),
      flexDirection(Row),
      justifyContent(SpaceBetween),
      position(Absolute),
      top(Pt(0.)),
      left(Pt(0.)),
      right(Pt(0.)),
      height(Pt(80.)),
    ]);
  let tabBarItem = isActive =>
    style([
      flex(1.),
      justifyContent(Center),
      alignItems(Center),
      backgroundColor(isActive ? String("tomato") : String("transparent")),
    ]);
  let tabBarItemText = isActive =>
    style([color(isActive ? String("white") : String("tomato"))]);
};

let component = ReasonReact.statelessComponent("CustomTabBar");

let make = (~tabBarProps: TabNavigator.tabBarProps, _children) => {
  ...component,
  render: _self =>
    <View style=Styles.tabBar>
      (
        tabBarProps.screens
        |> Array.mapi((index, screen: TabNavigator.screenConfig) => {
             let isActive = tabBarProps.currentRoute === screen.route;
             <TouchableOpacity
               key=(string_of_int(index))
               style=(Styles.tabBarItem(isActive))
               onPress=(_e => tabBarProps.jumpTo(screen.route))>
               (screen.tabItem({isActive: isActive}))
             </TouchableOpacity>;
           })
        |> ReasonReact.arrayToElement
      )
    </View>,
};