open Rebolt;

module Styles = {
  open Style;
  let tabBar =
    style([
      flex(1.),
      flexDirection(Row),
      justifyContent(SpaceBetween),
      position(Absolute),
      height(Pt(40.)),
      top(Pt(0.)),
      left(Pt(0.)),
      right(Pt(0.)),
    ]);
  let tabBarItemContainer =
    switch (Platform.os()) {
    | Platform.Android =>
      style([flex(1.), justifyContent(Center), alignItems(Center)])
    | _ => style([flex(1.), justifyContent(Center), alignItems(Center)])
    };
  let tabBarItem = _isActive =>
    style([flex(1.), justifyContent(Center), alignItems(Center)]);
  let tabBarItemText = isActive =>
    style([color(isActive ? String("white") : String("tomato"))]);
  let tabBarIndicator = (denominator, itemIndex) => {
    let itemWidth =
      float_of_int(Dimensions.get(`window)##width) /. denominator;
    style([
      position(Absolute),
      bottom(Pt(0.)),
      height(Pt(2.)),
      marginLeft(Pt(itemWidth *. float_of_int(itemIndex))),
      backgroundColor(String("white")),
      width(Pt(itemWidth)),
      zIndex(1),
    ]);
  };
};

let component = ReasonReact.statelessComponent("CustomTabBar");

let make =
    (~tabBarProps: NavigationConfig.TabNavigator.tabBarProps, _children) => {
  ...component,
  render: _self =>
    <View style=Styles.tabBar>
      (
        tabBarProps.screens
        |> Array.mapi(
             (index, screen: NavigationConfig.TabNavigator.screenConfig) => {
             let isActive = tabBarProps.currentRoute === screen.route;
             isActive ?
               <Animated.View
                 key=(string_of_int(index))
                 style=(
                   Styles.tabBarIndicator(
                     float_of_int(Array.length(tabBarProps.screens)),
                     index,
                   )
                 )
               /> :
               ReasonReact.null;
           })
        |> ReasonReact.array
      )
      (
        tabBarProps.screens
        |> Array.mapi(
             (index, screen: NavigationConfig.TabNavigator.screenConfig) => {
             let isActive = tabBarProps.currentRoute === screen.route;
             <TouchableWithoutFeedback
               key=(string_of_int(index))
               style=(Styles.tabBarItem(isActive))
               onPress=(_e => tabBarProps.jumpTo(screen.route))>
               <View style=Styles.tabBarItemContainer>
                 (screen.tabItem({isActive: isActive}))
               </View>
             </TouchableWithoutFeedback>;
           })
        |> ReasonReact.array
      )
    </View>,
};