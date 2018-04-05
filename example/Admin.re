open BsReactNative;

let component = ReasonReact.statelessComponent("Admin");

module Styles = {
  let container =
    Style.(style([flex(1.), justifyContent(Center), alignItems(Center)]));
};

let renderButtons = (~push, ~pop) =>
  <View>
    <TouchableOpacity onPress=(_e => push())>
      <Text> (ReasonReact.stringToElement("Push")) </Text>
    </TouchableOpacity>
    <TouchableOpacity onPress=(_e => pop())>
      <Text> (ReasonReact.stringToElement("Pop")) </Text>
    </TouchableOpacity>
  </View>;

let make = (~push, ~pop, _children) => {
  ...component,
  render: _self =>
    <View>
      <Text> (ReasonReact.stringToElement("Admin")) </Text>
      (renderButtons(~push, ~pop))
    </View>
};
