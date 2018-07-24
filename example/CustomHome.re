open Rebolt;

let component = ReasonReact.statelessComponent("CustomHome");

let make = (~navigation, _children) => {
  ...component,
  render: _self =>
    <NavigationConfig.TabNavigator.Screen
      navigation
      tabItem=(
        ({isActive}) =>
          <NavigationConfig.TabNavigator.TabBar.Item
            label="Home"
            style=Style.(
                    style([
                      color(isActive ? String("blue") : String("gray")),
                    ])
                  )
          />
      )>
      ...(() => <Text> (ReasonReact.string("Home")) </Text>)
    </NavigationConfig.TabNavigator.Screen>,
};