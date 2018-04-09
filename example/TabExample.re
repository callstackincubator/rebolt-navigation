open BsReactNative;

open Navigation;

module Styles = {
  open Style;
  let tabBar =
    style([
      flexDirection(Row),
      backgroundColor(String("#efedec")),
      height(Pt(49.)),
      position(Absolute),
      left(Pt(0.0)),
      right(Pt(0.0)),
      bottom(Pt(0.0)),
    ]);
  let tabBarItem =
    style([flex(1.), justifyContent(Center), alignItems(Center)]);
  let tabBarItemText = isCurrentRoute =>
    style([color(String(isCurrentRoute ? "#157efb" : "#a0a0a0"))]);
  let iconContainer =
    style([
      flexDirection(Column),
      justifyContent(Center),
      alignItems(Center),
    ]);
  let likeIcon = style([width(Pt(18.)), height(Pt(18.))]);
  let iconLabel = isCurrentRoute =>
    style([
      fontSize(Float(10.)),
      color(String(isCurrentRoute ? "#157efb" : "#a0a0a0")),
      marginTop(Pt(2.)),
    ]);
};

module TabBar = {
  let component = ReasonReact.statelessComponent("TabBar");
  let make =
      (
        ~currentRoute,
        ~routes,
        ~navigation: TabNavigator.navigation,
        _children,
      ) => {
    ...component,
    render: _self =>
      <View style=Styles.tabBar>
        (
          routes
          |> Array.mapi((index, route) => {
               let isCurrentRoute = currentRoute === route;
               let tabBarItem =
                 switch (route, isCurrentRoute) {
                 | (Config.Feed, isCurrentRoute) =>
                   <Text style=(Styles.tabBarItemText(isCurrentRoute))>
                     (ReasonReact.stringToElement("Feed"))
                   </Text>
                 | (Config.Likes, true) =>
                   <View style=Styles.iconContainer>
                     <Image
                       style=Styles.likeIcon
                       source=(
                         Required(
                           Packager.require("../../../example/like-red.png"),
                         )
                       )
                     />
                     <Text style=(Styles.iconLabel(true))>
                       (ReasonReact.stringToElement("Likes"))
                     </Text>
                   </View>
                 | (Config.Likes, false) =>
                   <View style=Styles.iconContainer>
                     <Image
                       style=Styles.likeIcon
                       source=(
                         Required(
                           Packager.require("../../../example/like.png"),
                         )
                       )
                     />
                     <Text style=(Styles.iconLabel(false))>
                       (ReasonReact.stringToElement("Likes"))
                     </Text>
                   </View>
                 | (Config.About, isCurrentRoute) =>
                   <Text style=(Styles.tabBarItemText(isCurrentRoute))>
                     (ReasonReact.stringToElement("About"))
                   </Text>
                 | (_, _) => ReasonReact.nullElement
                 };
               <TouchableOpacity
                 key=(string_of_int(index))
                 style=Styles.tabBarItem
                 onPress=(_e => navigation.goToRoute(route))>
                 tabBarItem
               </TouchableOpacity>;
             })
          |> ReasonReact.arrayToElement
        )
      </View>,
  };
};

let component = ReasonReact.statelessComponent("TabExample");

let make = (~navigation as nav: StackNavigator.navigation, _children) => {
  ...component,
  render: _self =>
    <StackNavigator.Screen headerTitle="Tab example" navigation=nav>
      ...(
           () =>
             <TabNavigator
               initialRoute=Config.Feed
               routes=[|Config.Feed, Config.Likes, Config.About|]
               renderTabBar=(
                 (~routes, ~navigation, ~currentRoute) =>
                   <TabBar currentRoute routes navigation />
               )>
               ...(
                    (~currentRoute, ~navigation) =>
                      switch (currentRoute) {
                      | Config.Feed => <Feed navigation stackNavigation=nav />
                      | Config.Likes => <Likes />
                      | Config.About => <About />
                      | _ => <Feed navigation stackNavigation=nav />
                      }
                  )
             </TabNavigator>
         )
    </StackNavigator.Screen>,
};