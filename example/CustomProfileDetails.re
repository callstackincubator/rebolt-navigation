open BsReactNative;

open NavigationConfig;

open TabNavigator;

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