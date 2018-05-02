---
id: api-stack-navigator
title: Stack Navigator
sidebar_label: Stack Navigator
---

## Props

* `~initialState`: Array with initial route `array(Config.Route name)`, see [Config](get-started.html#usage),
* `~onStateChange?`: Function of type `tpersistedState => unit`, see [persistedState](api-stack-navigator.html#persistedstate),
* `~headerMode`: headerMode=?,

## Screen

props:

* `~navigation`: Navigation instance,
* `~style?`: BsReactNative.Style.t,
* `~headerTitle?`: string,
* `~headerStyle?`: BsReactNative.Style.t,
* `~headerLeft?`: [Header.props](api-stack-navigator.html#header) => [returnsComponent](api-stack-navigator.html#returnscomponent),
* `~headerCenter?`: [Header.props](api-stack-navigator.html#header) => [returnsComponent](api-stack-navigator.html#returnscomponent),
* `~headerRight?`: [Header.props](api-stack-navigator.html#header) => [returnsComponent](api-stack-navigator.html#returnscomponent),
* `~animation?`: Animation,

## Header

### Props

* `~headerProps`: [props](api-stack-navigator.html#headerprops)

### HeaderProps

* `screens`: array([screen](api-stack-navigator.html#screen)),
* `activeScreen`: int,
* `animatedValue`: Animated.Value.t,
* `pop`: string => unit,

## Types

### persistedState

`array(Config.route)`

### screen

* `header`: [config](api-stack-navigator.html#config),
* `animation`: Animation.t,
* `key`: string,
  }

### config

* `style`: option(BsReactNative.Style.t),
* `title`: option(string),
* `center`: option([returnsComponent](api-stack-navigator.html#returnscomponent)),
* `left`: option([returnsComponent](api-stack-navigator.html#returnscomponent)),
* `right`: option([returnsComponent](api-stack-navigator.html#returnscomponent)),

### returnsComponent

`props => ReasonReact.reactElement`
