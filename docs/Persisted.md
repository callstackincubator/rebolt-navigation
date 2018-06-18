---
id: persisted
title: Persisted state
sidebar_label: Persisted state
---

## Introduction

In some cases, it's a good idea to keep your navigation history e.g. If someone closes the app and opens it again, it expects to be on the last visited screen.

We can quickly do this using `AsyncStorage` and adding few modifications in your main component where you define `StackNavigator`.

## Component

First, define your main component with `reducerComponent`:

```js
let component = ReasonReact.reducerComponent('Main');
```

## State

Define the type of your state:

```js
type state = {persistedState: option(StackNavigator.persistedState)};
```

## Actions

```js
type action =
    | Rehydrate(StackNavigator.persistedState);
```

## Initial state

Now it is time to define the `main` method of our component.

Let's start from initial state:

```js
let make = _children => {
    ...component,
    initialState: () => {persistedState: None},
```

## Reducer

We need to define `reducer` method to handle our actions

```js
reducer: (action, _state) =>
  switch (action) {
  | Rehydrate(state) =>
    ReasonReact.Update({persistedState: Some(state)})
  },
```

## didUpdate

Next step is to define `didUpdate` component lifecycle method.
Here we use `AsyncStorage` to get our routes from `AsyncStorage` if any exists.
If any routes config exists, then we do rehydrate our state. Otherwise, we use the default configuration.

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

## StackNavigator

The last thing is to render StackNavigator with `initialState` and `onStateChange` props

```js
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
```

## Full Example

```js
open NavigationConfig;

open Rebolt;

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
