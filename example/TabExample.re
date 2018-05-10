open BsReactNative;

open NavigationConfig;

let component = ReasonReact.statelessComponent("Profile");

let make = (~navigation as nav: StackNavigator.navigation, _children) => {
  ...component,
  render: _self =>
    <StackNavigator.Screen headerTitle="Profile" headerStyle=Style.(style([elevation(0.)])) navigation=nav>
      ...(
           () =>
             <TabNavigator
               initialRoute=Config.ContactList
               routes=[|Config.ContactList, Config.Messages, Config.About|]>
               ...(
                    (~navigation) =>
                      switch (navigation.currentRoute) {
                      | Config.ContactList =>
                        <ContactList
                          navigation
                          stackNavigation=nav
                          custom=false
                        />
                      | Config.Messages => <Messages navigation custom=false />
                      | _ => <Settings navigation stackNavigation=nav />
                      }
                  )
             </TabNavigator>
         )
    </StackNavigator.Screen>,
};