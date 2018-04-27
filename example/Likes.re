open Navigation;

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
    <TabNavigator.Screen tabItem=(Label("Likes")) navigation>
      ...(
           () =>
             <View style=Styles.container>
               <Text style=Style.(style([fontSize(Float(24.))]))>
                 (ReasonReact.stringToElement("Likes"))
               </Text>
             </View>
         )
    </TabNavigator.Screen>,
};