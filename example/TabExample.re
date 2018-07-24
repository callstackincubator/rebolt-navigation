open Rebolt;

module Styles = {
  open Style;
  let header = style([elevation(0.)]);
};

let component = ReasonReact.statelessComponent("Profile");

let make = (~navigation as nav: NavigationConfig.StackNavigator.navigation, _children) => {
  ...component,
  render: _self => (
      <NavigationConfig.StackNavigator.Screen
        headerTitle="Profile" headerStyle=Styles.header navigation=nav>
        ...(
             () =>
               <NavigationConfig.TabNavigator
                 initialRoute=NavigationConfig.Config.ContactList
                 routes=[|NavigationConfig.Config.ContactList, NavigationConfig.Config.Messages, NavigationConfig.Config.About|]>
                 ...(
                      (~navigation) =>
                        switch (navigation.currentRoute) {
                        | NavigationConfig.Config.ContactList =>
                          <ContactList
                            navigation
                            stackNavigation=nav
                            custom=false
                          />
                        | NavigationConfig.Config.Messages =>
                          <Messages navigation custom=false />
                        | _ => <Settings navigation stackNavigation=nav />
                        }
                    )
               </NavigationConfig.TabNavigator>
           )
      </NavigationConfig.StackNavigator.Screen>
  )
};