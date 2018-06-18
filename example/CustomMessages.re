open Rebolt;

open NavigationConfig;

open TabNavigator;

let component = ReasonReact.statelessComponent("CustomMessages");

let make = (~navigation, _children) => {
  ...component,
  render: _self =>
    <Screen
      navigation
      tabItem=(
        ({isActive}) =>
          <TabBar.Item
            label="Messages"
            style=Style.(
                    style([
                      color(isActive ? String("blue") : String("gray")),
                    ])
                  )
          />
      )>
      ...(() => <Text> (ReasonReact.string("Messages")) </Text>)
    </Screen>,
};