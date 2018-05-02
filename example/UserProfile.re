open NavigationConfig;

open BsReactNative;

let screenWidth = Dimensions.get(`screen)##width;

module Style = {
  open Style;
  let container =
    style([flex(1.), alignItems(Center), justifyContent(Center)]);
  let text = style([fontWeight(`_600), fontSize(Float(20.))]);
};

let component = ReasonReact.statelessComponent("UserProfile");

let make = (~navigation: StackNavigator.navigation, _children) => {
  ...component,
  render: _self =>
    <StackNavigator.Screen navigation headerTitle="User profile">
      ...(
           () =>
             <View style=Style.container>
               <Text style=Style.text>
                 (ReasonReact.stringToElement("User profile"))
               </Text>
               <TouchableOpacity
                 onPress=(_e => navigation.push(Config.Admin))>
                 <Text style=Style.text>
                   (ReasonReact.stringToElement("Go to Admin"))
                 </Text>
               </TouchableOpacity>
             </View>
         )
    </StackNavigator.Screen>,
};