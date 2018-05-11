open BsReactNative;

open NavigationConfig;

open TabNavigator;

let component = ReasonReact.statelessComponent("CustomHome");

let make = (~navigation, _children) => {
  ...component,
  render: _self =>
    <Screen
      navigation
      tabItem=(
        ({isActive}) =>
          <TabBar.Item
            label="Home"
            style=Style.(
                    style([
                      color(isActive ? String("blue") : String("gray")),
                    ])
                  )
          />
      )>
      ...(() => <Text> (ReasonReact.string("Home")) </Text>)
    </Screen>,
};