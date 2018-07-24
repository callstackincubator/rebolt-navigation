open Rebolt;

let component = ReasonReact.statelessComponent("Admin");

module Styles = {
  open Style;
  let container =
    style([flex(1.), justifyContent(Center), alignItems(Center)]);
  let button = color =>
    style([
      flex(1.),
      justifyContent(Center),
      paddingHorizontal(Pt(20.)),
      maxHeight(Pt(40.)),
      marginTop(Pt(16.)),
      backgroundColor(String(color)),
      borderRadius(20.),
      width(Pt(100.)),
    ]);
  let buttonText = style([textAlign(Center)]);
  let title = style([fontSize(Float(20.))]);
};

let renderButtons = (nav: NavigationConfig.StackNavigator.navigation) =>
  <View>
    <TouchableOpacity
      style=(Styles.button("#4cd964"))
      onPress=(_e => nav.push(NavigationConfig.Config.Home))>
      <Text style=Styles.buttonText> (ReasonReact.string("Push")) </Text>
    </TouchableOpacity>
    <TouchableOpacity
      style=(Styles.button("#ff9500")) onPress=(_e => nav.pop())>
      <Text style=Styles.buttonText> (ReasonReact.string("Pop")) </Text>
    </TouchableOpacity>
  </View>;

let make = (~navigation, _children) => {
  ...component,
  render: _self =>
    <NavigationConfig.StackNavigator.Screen
      headerTitle="Admindkasldkasldkdasdas"
      navigation
      headerStyle=Style.(style([backgroundColor(String("#FFF"))]))>
      ...(
           () =>
             <View style=Styles.container>
               <Text style=Styles.title>
                 (ReasonReact.string("Admin screen"))
               </Text>
               (renderButtons(navigation))
             </View>
         )
    </NavigationConfig.StackNavigator.Screen>,
};