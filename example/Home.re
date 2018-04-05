open BsReactNative;

let component = ReasonReact.statelessComponent("Home");

let make = (~push, ~pop, _children) => {
  ...component,
  render: _self =>
    <View>
      <View>
        <Text> (ReasonReact.stringToElement("Home")) </Text>
        <View>
          <TouchableOpacity onPress=(_e => push())>
            <Text> (ReasonReact.stringToElement("Push")) </Text>
          </TouchableOpacity>
          <TouchableOpacity onPress=(_e => pop())>
            <Text> (ReasonReact.stringToElement("Pop")) </Text>
          </TouchableOpacity>
        </View>
      </View>
    </View>
};

