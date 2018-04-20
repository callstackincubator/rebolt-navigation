open Navigation;

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
               renderTabBar=((~tabBarProps) => <CustomTabBar tabBarProps />)>
               ...(
                    (~navigation) =>
                      switch (navigation.currentRoute) {
                      | Config.Feed => <Feed navigation stackNavigation=nav />
                      | Config.Likes => <Likes navigation />
                      | Config.About => <About navigation />
                      | _ => <Feed navigation stackNavigation=nav />
                      }
                  )
             </TabNavigator>
         )
    </StackNavigator.Screen>,
};