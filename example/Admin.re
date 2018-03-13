open Navigation;

open BsReactNative;

let component = ReasonReact.statelessComponent("Admin");

module Styles = {
  let container =
    Style.(style([flex(1.), justifyContent(Center), alignItems(Center)]));
};

let renderButtons = (nav: StackNavigator.navigation) =>
  <View>
    <TouchableOpacity
      onPress=(_e => nav.send(StackNavigator.Push(Config.Home)))>
      <Text> (ReasonReact.stringToElement("Push")) </Text>
    </TouchableOpacity>
    <TouchableOpacity onPress=(_e => nav.send(StackNavigator.Pop))>
      <Text> (ReasonReact.stringToElement("Pop")) </Text>
    </TouchableOpacity>
  </View>;

let make = (~navigation, _children) => {
  ...component,
  render: _self =>
    <Screen
      headerTitle="Admin"
      animation=(
        opts =>
          StackNavigator.Animation.(
            switch (opts.transition, opts.action) {
            | ((_, Config.Home), Push) => fadeInOut
            | ((_, Config.Home), Pop) => slideInOut
            | ((Config.Home, _), Push) => fadeInOut
            | _ => fadeInOut
            }
          )(
            opts
          )
      )
      navigation>
      ...(
           () =>
             <View>
               <Text> (ReasonReact.stringToElement("Admin")) </Text>
               (renderButtons(navigation))
             </View>
         )
    </Screen>
};
