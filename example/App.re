open Rebolt;

module Main = {
  let component = ReasonReact.statelessComponent("Main");
  let make = _children => {
    ...component,
    render: _self =>
      NavigationConfig.(
        <NavigationConfig.StackNavigator
          initialState=[|Config.Welcome|]
          onStateChange=(
            state =>
              AsyncStorage.setItem(
                "$state",
                state
                |> NavigationConfig.StackNavigator.Persistence.encode
                |> Js.Json.stringify,
                (),
              )
              |> ignore
          )>
          ...(
               (~currentRoute, ~navigation) =>
                 switch (currentRoute) {
                 | Config.TabExample => <TabExample navigation />
                 | Config.Home => <Home navigation />
                 | Config.Admin => <Admin navigation />
                 | Config.Welcome => <Welcome navigation />
                 | Config.UserProfile => <UserProfile navigation />
                 | Config.CustomTabBarExample =>
                   <CustomTabBarExample navigation />
                 | _ => <TabExample navigation />
                 }
             )
        </NavigationConfig.StackNavigator>
      ),
  };
};

let app = () => <Main />;