open NavigationConfig;

open BsReactNative;

let component = ReasonReact.statelessComponent("Home");

module Styles = {
  open Style;
  let continer =
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

let renderButtons = (nav: StackNavigator.navigation) =>
  <View>
    <TouchableOpacity
      style=(Styles.button("#4cd964"))
      onPress=(_e => nav.push(Config.Admin))>
      <Text style=Styles.buttonText> (ReasonReact.string("Push")) </Text>
    </TouchableOpacity>
    <TouchableOpacity
      style=(Styles.button("#ff9500")) onPress=(_e => nav.pop())>
      <Text style=Styles.buttonText> (ReasonReact.string("Pop")) </Text>
    </TouchableOpacity>
  </View>;

let make = (~navigation as nav: StackNavigator.navigation, _children) => {
  ...component,
  render: _self =>
    <StackNavigator.Screen headerTitle="Home" navigation=nav>
      ...(
           () =>
             <View style=Styles.continer>
               <Text style=Styles.title>
                 (ReasonReact.string("Home screen"))
               </Text>
               (renderButtons(nav))
             </View>
         )
    </StackNavigator.Screen>,
};