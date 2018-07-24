open Rebolt;

module Styles = {
  open Style;
  let header = style([elevation(0.), backgroundColor(String("#37bc9b"))]);
};

let component = ReasonReact.statelessComponent("CustomTabBarExample");

let make =
    (
      ~navigation as nav: NavigationConfig.StackNavigator.navigation,
      _children,
    ) => {
  ...component,
  render: _self =>
    NavigationConfig.(
      <NavigationConfig.StackNavigator.Screen
        headerTitle="CustomTabBarExample"
        headerStyle=Styles.header
        navigation=nav>
        ...(
             () =>
               <NavigationConfig.TabNavigator
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
               </NavigationConfig.TabNavigator>
           )
      </NavigationConfig.StackNavigator.Screen>
    ),
};