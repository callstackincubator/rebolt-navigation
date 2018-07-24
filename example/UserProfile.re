open Rebolt;

let screenWidth = Dimensions.get(`screen)##width;

module Style = {
  open Style;
  let container =
    style([flex(1.), alignItems(Center), justifyContent(Center)]);
  let text = style([fontWeight(`_600), fontSize(Float(20.))]);
};

let component = ReasonReact.statelessComponent("UserProfile");

let make =
    (~navigation: NavigationConfig.StackNavigator.navigation, _children) => {
  ...component,
  render: _self =>
    <NavigationConfig.StackNavigator.Screen
      navigation headerTitle="User profile">
      ...(
           () =>
             <View style=Style.container>
               <Text style=Style.text>
                 (ReasonReact.string("User profile"))
               </Text>
               <TouchableOpacity
                 onPress=(
                   _e => navigation.push(NavigationConfig.Config.Admin)
                 )>
                 <Text style=Style.text>
                   (ReasonReact.string("Go to Admin"))
                 </Text>
               </TouchableOpacity>
             </View>
         )
    </NavigationConfig.StackNavigator.Screen>,
};