open BsReactNative;

open Navigation;

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

module Home = {
  let component = ReasonReact.statelessComponent("Home");
  let make = (~navigation: StackNavigator.navigation, _children) => {
    ...component,
    render: _self =>
      <View
        style=Style.(
                style([flex(1.), justifyContent(Center), alignItems(Center)])
              )>
        <Text> (ReasonReact.stringToElement("Home")) </Text>
        (renderButtons(navigation))
      </View>
  };
};

module Admin = {
  let component = ReasonReact.statelessComponent("Admin");
  let make = (~navigation: StackNavigator.navigation, _children) => {
    ...component,
    render: _self =>
      <View
        style=Style.(
                style([flex(1.), justifyContent(Center), alignItems(Center)])
              )>
        <Text> (ReasonReact.stringToElement("Admin")) </Text>
        (renderButtons(navigation))
      </View>
  };
};

module Main = {
  let component = ReasonReact.statelessComponent("App");
  let make = _children => {
    ...component,
    render: _self =>
      <StackNavigator initialRoute=Config.Admin>
        ...(
             (~currentRoute, ~navigation) =>
               switch currentRoute {
               | Config.Admin => <Admin navigation />
               | Config.Home => <Home navigation />
               }
           )
      </StackNavigator>
  };
};

let app = () => <Main />;
