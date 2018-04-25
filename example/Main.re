open Navigation;

open BsReactNative;

module Main = {
  type state = {persistedState: StackNavigator.persistedState};
  type action =
    | Rehydrate(StackNavigator.persistedState);
  let component = ReasonReact.reducerComponent("Main");
  let make = _children => {
    ...component,
    didMount: self => {
      AsyncStorage.getItem(
        "$state",
        ~callback=
          (_, value) =>
            switch (value) {
            | Some(state) =>
              self.send(
                Rehydrate(
                  state
                  |> Js.Json.parseExn
                  |> StackNavigator.Persistence.decode,
                ),
              )
            | None => ()
            },
        (),
      );
      ReasonReact.NoUpdate;
    },
    reducer: (action, state) =>
      switch (action) {
      | Rehydrate(state) => ReasonReact.Update({persistedState: state})
      },
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