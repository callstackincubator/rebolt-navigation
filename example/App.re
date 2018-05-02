open NavigationConfig;

open BsReactNative;

module Main = {
  type state = {persistedState: option(StackNavigator.persistedState)};
  type action =
    | Rehydrate(StackNavigator.persistedState);
  let component = ReasonReact.reducerComponent("Main");
  let make = _children => {
    ...component,
    initialState: () => {persistedState: None},
    didMount: self => {
      AsyncStorage.getItem(
        "$state",
        ~callback=
          (_, value) =>
            self.send(
              Rehydrate(
                switch (value) {
                | Some(state) =>
                  state
                  |> Js.Json.parseExn
                  |> StackNavigator.Persistence.decode
                | None => [|Config.Welcome|]
                },
              ),
            ),
        (),
      );
      ReasonReact.NoUpdate;
    },
    reducer: (action, state) =>
      switch (action) {
      | Rehydrate(state) =>
        ReasonReact.Update({persistedState: Some(state)})
      },
    render: self =>
      switch (self.state.persistedState) {
      | Some(state) =>
        <StackNavigator
          initialState=state
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
        </StackNavigator>
      | None => <View />
      },
  };
};

let app = () => <Main />;