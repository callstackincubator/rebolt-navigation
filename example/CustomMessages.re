open Rebolt;

let component = ReasonReact.statelessComponent("CustomMessages");

let make = (~navigation, _children) => {
  ...component,
  render: _self =>
    <NavigationConfig.TabNavigator.Screen
      navigation
      tabItem=(
        ({isActive}) =>
          <NavigationConfig.TabNavigator.TabBar.Item
            label="Messages"
            style=Style.(
                    style([
                      color(isActive ? String("blue") : String("gray")),
                    ])
                  )
          />
      )>
      ...(() => <Text> (ReasonReact.string("Messages")) </Text>)
    </NavigationConfig.TabNavigator.Screen>,
};