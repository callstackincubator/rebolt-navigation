---
id: tab-navigator
title: Tab Navigator
sidebar_label: Tab Navigator
---

It allows you to navigate between the screens with a use of tabs. Tab bar is usually located on the bottom or on the top of the screen.

As we mentioned in [usage](get-started.html#usage) section you need to configure your navigation.

```reason
module Config = {
  type route =
    | Feed
    | Likes
    | About;
};
```

## TabNavigator

`TabNavigator` requires initial route, the screen that will be showed first. In our case it will be `Config.About`. In addition we need to specify what routes are going to represent our tabs, we do it by passing an array of routes to `routes` prop.

ReRoute provides a default Tab Bar for iOS and Android, but if you want to use a custom one, use the optional prop `renderTabBar`.
`renderTabBar` prop gives you a `tabBarProps` which consist all of the data you will need to build your custom Tab Bar with.

`TabNavigator` also provides you with the `navigation` render prop, which you will use to pattern match on `navigation.currentRoute`.

Let's see an example to what we described above:

```reason
<TabNavigator
  initialRoute=Config.About
  routes=[|Config.Feed, Config.Likes, Config.About|]
  renderTabBar=((~tabBarProps) => <CustomTabBar tabBarProps />)>
  ...(
      (~navigation) =>
        switch (navigation.currentRoute) {
        | Config.Feed => <Feed navigation />
        | Config.Likes => <Likes navigation />
        | Config.About => <About navigation />
        }
    )
</TabNavigator>
```

## Screen

Every component that is rendered by `TabNavigator` needs to be wrapped in `Screen` component. That allows you to customize `TabBar` item as you like by setting `tabItem` props. `tabItem` it is a function that receives `tabItemProps` e.g. `isActive` which indicate whether the tab is active or not. Returned can be any component or you can use default `TabBar.Item`. `TabBar.Item` and pass props like: `label`, `icon` or `style`. `TabNavigator.Screen` component requires you to pass the navigation prop that you receive from the `TabNavigator`. This is way in the example above we passed the `navigation` prop to every single component that is rendered by `TabNavigator`.
Here is how you could use the `Screen` component:

**Feed.re**

```reason
open NavigationConfig;

open BsReactNative;

module Styles = {
  open Style;
  let container =
    style([flex(1.), alignItems(Center), justifyContent(Center)]);
};

let component = ReasonReact.statelessComponent("Feed");

let make = (~navigation, _children) => {
  ...component,
  render: _self =>
    <TabNavigator.Screen
      tabItem=(
        ({isActive}) =>
          <TabBar.Item
            label="Contacts"
            style=(
              Style.style([Style.color(String(isActive ? "blue" : "gray"))])
            )
      navigation>
      ...(
           () =>
             <View style=Styles.container>
               <Text> (ReasonReact.string("Feed")) </Text>
             </View>
         )
    </TabNavigator.Screen>,
};
```
