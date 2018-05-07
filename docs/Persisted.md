---
id: persisted
title: Persisted state
sidebar_label: Persisted state
---

If you would like to keep your navigation history, you can use asyncstorage.
In your main component, there where you define `StackNavigator`.

First define `reducerComponent`:

```js
let component = ReasonReact.reducerComponent('Main');
```

Now we need to define a type of component state and our actions:

State:

```js
type state = {persistedState: option(StackNavigator.persistedState)};
```

Actions:

```js
type action =
    | Rehydrate(StackNavigator.persistedState);
```

Now is time to define the `main` method of our component.

We start from initial state:

```js
let make = _children => {
    ...component,
    initialState: () => {persistedState: None},
...
```

We need to define `reducer` method to handle our actions

```js
reducer: (action, _state) =>
  switch (action) {
  | Rehydrate(state) =>
    ReasonReact.Update({persistedState: Some(state)})
  },
```

Our next step is to define `didUpdate` component lifecycle method. Here we used `AsyncStorage` to store our routes and rehydrate action from our component.

```js
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
```

The last think is to render StackNavigator with `initialState` and `onStateChange`

`onStateChange`:

```js
(
  state =>
    AsyncStorage.setItem(
      "$state",
      state |> StackNavigator.Persistence.encode |> Js.Json.stringify,
      (),
    )
    |> ignore
)
```

### Full Example:

```js
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
    reducer: (action, _state) =>
      switch (action) {
      | Rehydrate(state) =>
        ReasonReact.Update({persistedState: Some(state)})
      },
    render: self =>
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
  };
};

let app = () => <Main />;
```
