open Navigation;

open TabNavigator;

open BsReactNative;

module Styles = {
  open Style;
  let container =
    style([flex(1.), alignItems(Center), justifyContent(Center)]);
};

let component = ReasonReact.statelessComponent("Likes");

let make = (~navigation, _children) => {
  ...component,
  render: _self =>
    <Screen
      tabItem=(
        ({isActive}) =>
          <TabBar.Item
            label="Likes"
            style=(
              Style.style([Style.color(String(isActive ? "red" : "gray"))])
            )
          />
      )
      navigation>
      ...(
           () =>
             <View style=Styles.container>
               <Text style=Style.(style([fontSize(Float(24.))]))>
                 (ReasonReact.stringToElement("Likes"))
               </Text>
             </View>
         )
    </Screen>,
};