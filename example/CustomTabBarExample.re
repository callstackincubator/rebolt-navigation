open BsReactNative;

open NavigationConfig;

open TabNavigator;

module CustomHome = {
  let component = ReasonReact.statelessComponent("CustomHome");
  let make = (~navigation, _children) => {
    ...component,
    render: _self =>
      <Screen
        navigation
        tabItem=(
          ({isActive}) =>
            <TabBar.Item
              label="Home"
              style=Style.(
                      style([
                        color(isActive ? String("blue") : String("gray")),
                      ])
                    )
            />
        )>
        ...(() => <Text> (ReasonReact.string("Home")) </Text>)
      </Screen>,
  };
};

module CustomMessages = {
  let component = ReasonReact.statelessComponent("CustomMessages");
  let make = (~navigation, _children) => {
    ...component,
    render: _self =>
      <Screen
        navigation
        tabItem=(
          ({isActive}) =>
            <TabBar.Item
              label="Messages"
              style=Style.(
                      style([
                        color(isActive ? String("blue") : String("gray")),
                      ])
                    )
            />
        )>
        ...(() => <Text> (ReasonReact.string("Messages")) </Text>)
      </Screen>,
  };
};

module CustomProfileDetails = {
  let component = ReasonReact.statelessComponent("CustomProfileDetails");
  let make = (~navigation, _children) => {
    ...component,
    render: _self =>
      <Screen
        navigation
        tabItem=(
          ({isActive}) =>
            <TabBar.Item
              label="Details"
              style=Style.(
                      style([
                        color(isActive ? String("#fff") : String("#eee")),
                        fontSize(Float(16.)),
                      ])
                    )
            />
        )>
        ...(
             () =>
               <View
                 style=Style.(
                         style([
                           flex(1.),
                           alignItems(Center),
                           justifyContent(Center),
                         ])
                       )>
                 <Text
                   style=Style.(
                           style([
                             fontSize(Float(32.)),
                             color(String("#fff")),
                           ])
                         )>
                   (ReasonReact.string("Details screen"))
                 </Text>
               </View>
           )
      </Screen>,
  };
};

module CustomProfileStats = {
  let component = ReasonReact.statelessComponent("CustomProfileStats");
  let make = (~navigation, _children) => {
    ...component,
    render: _self =>
      <Screen
        navigation
        tabItem=(
          ({isActive}) =>
            <TabBar.Item
              label="Stats"
              style=Style.(
                      style([
                        color(isActive ? String("#fff") : String("#eee")),
                        fontSize(Float(16.)),
                      ])
                    )
            />
        )>
        ...(
             () =>
               <View
                 style=Style.(
                         style([
                           flex(1.),
                           alignItems(Center),
                           justifyContent(Center),
                         ])
                       )>
                 <Text
                   style=Style.(
                           style([
                             fontSize(Float(32.)),
                             color(String("#fff")),
                           ])
                         )>
                   (ReasonReact.string("Statistics screen"))
                 </Text>
               </View>
           )
      </Screen>,
  };
};

module CustomProfile = {
  module ProfileStyles = {
    open Style;
    let container = style([flex(1.), backgroundColor(String("#37bc9b"))]);
    let contentContainer = style([flex(1.)]);
    let profileContainer =
      style([
        justifyContent(Center),
        alignItems(Center),
        margin(Pt(16.)),
      ]);
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
                   renderTabBar=(
                     (~tabBarProps) => <CustomTabBar tabBarProps />
                   )>
                   ...(
                        (~navigation) =>
                          switch (navigation.currentRoute) {
                          | Config.CustomProfileDetails =>
                            <CustomProfileDetails navigation />
                          | _ => <CustomProfileStats navigation />
                          }
                      )
                 </TabNavigator>
               </View>
           )
      </Screen>,
  };
};

let component = ReasonReact.statelessComponent("CustomTabBarExample");

let make = (~navigation as nav: StackNavigator.navigation, _children) => {
  ...component,
  render: _self =>
    <StackNavigator.Screen headerTitle="CustomTabBarExample" headerStyle=Style.(style([elevation(0.)])) navigation=nav>
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