open NavigationConfig;

let component = ReasonReact.statelessComponent("CustomTabBarExample");

let make = (~navigation as nav: StackNavigator.navigation, _children) => {
  ...component,
  render: _self =>
    <StackNavigator.Screen headerTitle="CustomTabBarExample" navigation=nav>
      ...(
           () =>
             <TabNavigator
               initialRoute=Config.ContactList
               routes=[|Config.ContactList, Config.Messages, Config.About|]
               renderTabBar=((~tabBarProps) => <CustomTabBar tabBarProps />)>
               ...(
                    (~navigation) =>
                      switch (navigation.currentRoute) {
                      | Config.ContactList =>
                        <ContactList
                          navigation
                          stackNavigation=nav
                          custom=true
                        />
                      | Config.Messages => <Messages navigation custom=true />
                      | _ => <Settings navigation stackNavigation=nav />
                      }
                  )
             </TabNavigator>
         )
    </StackNavigator.Screen>,
};