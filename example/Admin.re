open Navigation;

open BsReactNative;

let component = ReasonReact.statelessComponent("Admin");

module Styles = {
  let container =
    Style.(style([flex(1.), justifyContent(Center), alignItems(Center)]));
};

let renderButtons = (nav: StackNavigator.navigation) =>
  <View>
    <TouchableOpacity onPress=(_e => nav.push(Config.Home))>
      <Text> (ReasonReact.stringToElement("Push")) </Text>
    </TouchableOpacity>
    <TouchableOpacity onPress=(_e => nav.pop())>
      <Text> (ReasonReact.stringToElement("Pop")) </Text>
    </TouchableOpacity>
  </View>;

let make = (~navigation, _children) => {
  ...component,
  render: _self =>
    <Screen headerTitle="Admin" navigation>
      ...(
           () =>
             <View>
               <Text> (ReasonReact.stringToElement("Admin")) </Text>
               (renderButtons(navigation))
             </View>
         )
    </Screen>
};