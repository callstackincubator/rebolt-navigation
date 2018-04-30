open NavigationConfig;

open BsReactNative;

module Styles = {
  open Style;
  let container =
    style([flex(1.), alignItems(Center), justifyContent(Center)]);
};

let component = ReasonReact.statelessComponent("About");

let make = (~navigation, _children) => {
  ...component,
  render: _self =>
    <TabNavigator.Screen label="About us" navigation>
      ...(
           () =>
             <View style=Styles.container>
               <Text style=Style.(style([fontSize(Float(24.))]))>
                 (ReasonReact.stringToElement("About"))
               </Text>
             </View>
         )
    </TabNavigator.Screen>,
};