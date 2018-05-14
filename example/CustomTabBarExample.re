open BsReactNative;

open NavigationConfig;

open TabNavigator;

let component = ReasonReact.statelessComponent("CustomTabBarExample");

let make = (~navigation as nav: StackNavigator.navigation, _children) => {
  ...component,
  render: _self =>
    <StackNavigator.Screen
      headerTitle="CustomTabBarExample"
      headerStyle=Style.(
                    style([elevation(0.), backgroundColor(String("#37bc9b"))])
                  )
      navigation=nav>
      ...(
           () =>
             <TabNavigator
               initialRoute=Config.CustomProfile
               routes=[|
                 Config.CustomHome,
                 Config.CustomMessages,
                 Config.CustomProfile,
               |]>
               ...(
                    (~navigation) =>
                      switch (navigation.currentRoute) {
                      | Config.CustomHome => <CustomHome navigation />
                      | Config.CustomMessages =>
                        <Messages navigation custom=false />
                      | _ => <CustomProfile navigation />
                      }
                  )
             </TabNavigator>
         )
    </StackNavigator.Screen>,
};