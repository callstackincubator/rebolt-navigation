open NavigationConfig;

let component = ReasonReact.statelessComponent("CustomTabBarExample");

let make = (~navigation as nav: StackNavigator.navigation, _children) => {
  ...component,
  render: _self =>
    <StackNavigator.Screen headerTitle="CustomTabBarExample" navigation=nav>
      ...(
           () =>
             <TabNavigator
               initialRoute=Config.Feed
               routes=[|Config.Feed, Config.Likes, Config.About|]
               renderTabBar=((~tabBarProps) => <CustomTabBar tabBarProps />)>
               ...(
                    (~navigation) =>
                      switch (navigation.currentRoute) {
                      | Config.Feed => <Feed navigation stackNavigation=nav />
                      | _ => <Feed navigation stackNavigation=nav />
                      }
                  )
             </TabNavigator>
         )
    </StackNavigator.Screen>,
};