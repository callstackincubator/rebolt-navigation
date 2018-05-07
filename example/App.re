open NavigationConfig;

open BsReactNative;

module Main = {
  let component = ReasonReact.statelessComponent("Main");
  let make = _children => {
    ...component,
    render: _self =>
      <StackNavigator
        initialState=[|Config.Welcome|]
        onStateChange=(
          state =>
            AsyncStorage.setItem(
              "$state",
              state |> StackNavigator.Persistence.encode |> Js.Json.stringify,
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
      </StackNavigator>,
  };
};

let app = () => <Main />;