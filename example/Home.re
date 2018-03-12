open Navigation;

open BsReactNative;

let component = ReasonReact.statelessComponent("Home");

let make = (~navigation as nav: StackNavigator.navigation, _children) => {
  ...component,
  render: _self =>
    <Screen
      headerTitle="Home"
      animation=(
        opts =>
          StackNavigator.Animation.(
            switch (opts.fromRoute, opts.toRoute) {
            | (Config.Home, Config.Admin) => fadeInOut
            | _ => slideInOut
            }
          )(
            opts
          )
      )
      navigation=nav>
      ...(
           () =>
             <View>
               <Text> (ReasonReact.stringToElement("Home")) </Text>
               <View>
                 <TouchableOpacity
                   onPress=(_e => nav.send(StackNavigator.Push(Config.Home)))>
                   <Text> (ReasonReact.stringToElement("Push")) </Text>
                 </TouchableOpacity>
                 <TouchableOpacity
                   onPress=(_e => nav.send(StackNavigator.Pop))>
                   <Text> (ReasonReact.stringToElement("Pop")) </Text>
                 </TouchableOpacity>
               </View>
             </View>
         )
    </Screen>
};
