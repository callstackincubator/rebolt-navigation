open NavigationConfig;

open TabNavigator;

open BsReactNative;

let component = ReasonReact.statelessComponent("Settings");

module Styles = {
  open Style;
  let container =
    style([flex(1.), alignItems(Center), justifyContent(Center)]);
  let title = style([color(String("#000")), fontSize(Float(24.))]);
  let button = color =>
    style([
      flex(1.),
      justifyContent(Center),
      paddingHorizontal(Pt(20.)),
      maxHeight(Pt(40.)),
      marginTop(Pt(16.)),
      backgroundColor(String(color)),
      borderRadius(20.),
    ]);
  let buttonText = style([color(String("white"))]);
};

let make =
    (~navigation, ~stackNavigation: StackNavigator.navigation, _children) => {
  ...component,
  render: _self =>
    <Screen
      tabItem=(
        ({isActive}) =>
          <TabBar.Item
            label="MySettings"
            style=(
              Style.style([Style.color(String(isActive ? "blue" : "gray"))])
            )
          />
      )
      navigation>
      ...(
           () =>
             <View style=Styles.container>
               <Text style=Styles.title>
                 (ReasonReact.stringToElement("My Settings"))
               </Text>
               <TouchableOpacity
                 onPress=(_e => navigation.jumpTo(Config.ContactList))>
                 <View style=(Styles.button("#2180f7"))>
                   <Text style=Styles.buttonText>
                     (ReasonReact.stringToElement("Go to contacts"))
                   </Text>
                 </View>
               </TouchableOpacity>
               <TouchableOpacity
                 onPress=(_e => navigation.jumpTo(Config.Messages))>
                 <View style=(Styles.button("#4cd964"))>
                   <Text style=Styles.buttonText>
                     (ReasonReact.stringToElement("Go to messages"))
                   </Text>
                 </View>
               </TouchableOpacity>
               <TouchableOpacity
                 onPress=(_e => stackNavigation.push(Config.Home))>
                 <View style=(Styles.button("#ff2242"))>
                   <Text style=Styles.buttonText>
                     (ReasonReact.stringToElement("Take me to stack"))
                   </Text>
                 </View>
               </TouchableOpacity>
             </View>
         )
    </Screen>,
};