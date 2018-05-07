---
id: stack-navigator
title: Stack Navigator
sidebar_label: Stack Navigator
---

Allows you to navigate between defined screens.

As we mentioned in [usage](get-started.html#usage) section you need to configure your navigation.

```reason
module Config = {
  type route =
    | Feed
    | Likes
    | About;
};
```

## Stack Navigator

`StackNavigator` requires initial route, the screen that will be showed fist, e.g. `Config.Welcome`.

Example:

```reason
<StackNavigator initialState=[|Config.Welcome|]>
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
```

StackNavigator Props:

| Name          | type                    | required |                                           |
| ------------- | ----------------------- | -------- | ----------------------------------------- |
| initialState  | array(NavigatorConfig)  | Yes      | [NavigatorConfig](get-started.html#usage) |
| onStateChange | navigationState => unit |          |                                           |

Render props:

| Name          | type       |                                           |
| ------------- | ---------- | ----------------------------------------- |
| ~currentRoute | Config     | [NavigatorConfig](get-started.html#usage) |
| ~navigation   | Navigation |                                           |

## Screen

Every component rendered in StackNavigator needs to be wrapped in `StackNavigator.Screen` component. This allows you pass an extra info to Stack Navigator like a label that will be showed in the Header. `StackNavigator.Screen` component requires you to pass the navigation prop that you receive from the `StackNavigator`. This is way in the example above we passed the `navigation` prop to every single component that is rendered by `StackNavigator`.

```reason
<StackNavigator.Screen
      headerTitle="Admin"
      navigation
      headerStyle=Style.(style([backgroundColor(String("#FFF"))]))>
      ...(
           () =>
             <View>
               <Text> (ReasonReact.string("Admin")) </Text>
             </View>
         )
    </StackNavigator.Screen>
```

Screen Props:

| Name        | type   |
| ----------- | ------ |
| headerTitle | String |
| headerStyle | Style  |
