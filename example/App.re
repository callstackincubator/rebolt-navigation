open Navigation;

open BsReactNative;

module Main = {
  let component = ReasonReact.statelessComponent("App");
  let make = _children => {
    ...component,
    render: _self =>
      <StackNavigator
        initialState=[|Config.TabExample|]
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
               | _ => <TabExample navigation />
               }
           )
      </StackNavigator>,
  };
};

let app = () => <Main />;