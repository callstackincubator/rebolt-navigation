open Navigation;

open BsReactNative;

let component = ReasonReact.statelessComponent("Home");

let make = (~navigation as nav: StackNavigator.navigation, _children) => {
  ...component,
  render: _self =>
    <Screen headerTitle="Home" navigation=nav>
      ...(
           () =>
             <View>
               <Text> (ReasonReact.stringToElement("Home")) </Text>
               <View>
                 <TouchableOpacity onPress=(_e => nav.push(Config.Admin))>
                   <Text> (ReasonReact.stringToElement("Push")) </Text>
                 </TouchableOpacity>
                 <TouchableOpacity onPress=(_e => nav.pop())>
                   <Text> (ReasonReact.stringToElement("Pop")) </Text>
                 </TouchableOpacity>
               </View>
             </View>
         )
    </Screen>,
};