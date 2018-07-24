open Rebolt;

module Styles = {
  open Style;
  let container =
    style([flex(1.), alignItems(Center), justifyContent(Center)]);
};

let component = ReasonReact.statelessComponent("About");

let make = (~navigation, _children) => {
  ...component,
  render: _self =>
    <NavigationConfig.TabNavigator.Screen
      tabItem=(
        ({isActive}) =>
          <NavigationConfig.TabNavigator.TabBar.Item
            label=""
            icon=(
              isActive ?
                URI(
                  Image.(
                    imageURISource(
                      ~uri="https://png.icons8.com/ios/1600/like.png",
                      (),
                    )
                  ),
                ) :
                URI(
                  Image.(
                    imageURISource(
                      ~uri="https://png.icons8.com/ios/1600/settings.png",
                      (),
                    )
                  ),
                )
            )
          />
      )
      navigation>
      ...(
           () =>
             <View style=Styles.container>
               <Text style=Style.(style([fontSize(Float(24.))]))>
                 (ReasonReact.string("About"))
               </Text>
             </View>
         )
    </NavigationConfig.TabNavigator.Screen>,
};