open Rebolt;

module Styles = {
  open Style;
  let container = style([flex(1.), backgroundColor(String("#37bc9b"))]);
  let contentContainer = style([flex(1.)]);
  let tabBarItem = isActive =>
    style([color(isActive ? String("blue") : String("gray"))]);
  let profileContainer =
    style([justifyContent(Center), alignItems(Center), margin(Pt(16.))]);
  let profileImg =
    style([
      height(Pt(100.)),
      width(Pt(100.)),
      borderRadius(50.),
      borderWidth(2.),
      borderColor(String("white")),
      margin(Pt(16.)),
    ]);
  let name =
    style([
      color(String("white")),
      fontSize(Float(18.)),
      fontWeight(`Bold),
    ]);
};

let component = ReasonReact.statelessComponent("CustomProfile");

let make = (~navigation, _children) => {
  ...component,
  render: _self =>
    <NavigationConfig.TabNavigator.Screen
      navigation
      tabItem=(
        ({isActive}) =>
          <NavigationConfig.TabNavigator.TabBar.Item
            label="Profile"
            style=(Styles.tabBarItem(isActive))
          />
      )>
      ...(
           () =>
             <View style=Styles.container>
               <View style=Styles.profileContainer>
                 <Image
                   style=Styles.profileImg
                   source=(
                     URI(
                       Image.(
                         imageURISource(
                           ~uri=
                             "https://randomuser.me/api/portraits/women/2.jpg",
                           (),
                         )
                       ),
                     )
                   )
                 />
                 <Text style=Styles.name>
                   (ReasonReact.string("Julia Chow"))
                 </Text>
               </View>
               <NavigationConfig.TabNavigator
                 initialRoute=NavigationConfig.Config.CustomProfileDetails
                 routes=[|
                   NavigationConfig.Config.CustomProfileDetails,
                   NavigationConfig.Config.CustomProfileStats,
                 |]
                 renderTabBar=((~tabBarProps) => <CustomTabBar tabBarProps />)>
                 ...(
                      (~navigation) =>
                        <View
                          style=Style.(
                                  style([flex(1.), marginTop(Pt(40.))])
                                )>
                          (
                            switch (navigation.currentRoute) {
                            | NavigationConfig.Config.CustomProfileDetails =>
                              <CustomProfileDetails navigation />
                            | _ => <CustomProfileStats navigation />
                            }
                          )
                        </View>
                    )
               </NavigationConfig.TabNavigator>
             </View>
         )
    </NavigationConfig.TabNavigator.Screen>,
};