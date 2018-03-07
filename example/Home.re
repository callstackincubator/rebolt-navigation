open Navigation;

open BsReactNative;

let component = ReasonReact.statelessComponent("Home");

let make = (~navigation as nav: StackNavigator.navigation, _children) => {
  ...component,
  render: _self =>
    <View
      style=Style.(
              style([flex(1.), justifyContent(Center), alignItems(Center)])
            )>
      <Header title="Home" navigation=nav />
      <Text> (ReasonReact.stringToElement("Home")) </Text>
      <View>
        <TouchableOpacity
          onPress=(_e => nav.send(StackNavigator.Push(Config.Home)))>
          <Text> (ReasonReact.stringToElement("Push")) </Text>
        </TouchableOpacity>
        <TouchableOpacity onPress=(_e => nav.send(StackNavigator.Pop))>
          <Text> (ReasonReact.stringToElement("Pop")) </Text>
        </TouchableOpacity>
      </View>
    </View>
};
