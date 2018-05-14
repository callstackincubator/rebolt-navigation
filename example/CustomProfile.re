open BsReactNative;

open NavigationConfig;

open TabNavigator;

module ProfileStyles = {
  open Style;
  let container = style([flex(1.), backgroundColor(String("#37bc9b"))]);
  let contentContainer = style([flex(1.)]);
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
    <Screen
      navigation
      tabItem=(
        ({isActive}) =>
          <TabBar.Item
            label="Profile"
            style=Style.(
                    style([
                      color(isActive ? String("blue") : String("gray")),
                    ])
                  )
          />
      )>
      ...(
           () =>
             <View style=ProfileStyles.container>
               <View style=ProfileStyles.profileContainer>
                 <Image
                   style=ProfileStyles.profileImg
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
                 <Text style=ProfileStyles.name>
                   (ReasonReact.string("Julia Chow"))
                 </Text>
               </View>
               <TabNavigator
                 initialRoute=Config.CustomProfileDetails
                 routes=[|
                   Config.CustomProfileDetails,
                   Config.CustomProfileStats,
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
                            | Config.CustomProfileDetails =>
                              <CustomProfileDetails navigation />
                            | _ => <CustomProfileStats navigation />
                            }
                          )
                        </View>
                    )
               </TabNavigator>
             </View>
         )
    </Screen>,
};