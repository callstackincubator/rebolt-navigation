---
id: api-tab-navigator
title: Tab Navigator
sidebar_label: Tab Navigator
---

## Props

* `~initialRoute`: Single `Config.RouteName`, see [Config](get-started.html#usage)
* `~routes`: array([Config.route](get-started.html#usage))
* `~navigation`: Navigation instance

## Screen

### Props

* `~navigation`: Navigation instance
* `~tabItem`: [tabItemProps](api-tab-navigator.html#tabitemprops) => `ReasonReact.reactElement`

## TabBar

### Props

* `~tabBarProps`: [tabBarProps](api-tab-navigator.html#tabbarprops)

## TabBarItem

### Props

* `~label`: `string`
* `~icon?`: `Rebolt.Image.imageSource`
* `~style?`: `Rebolt.Style.t`

## Types

### TabBarProps

* `screens`: array([screenConfig](api-tab-navigator.html#screenconfig))
* `currentRoute`: [Config.route](get-started.html#usage)
* `jumpTo`: `Config.route => unit`
* `indicatorColor`: option(`string`),

### screenConfig

* `route`: [Config.route](get-started.html#usage)
* `label`: `string`

### tabItemProps

* `isActive`: `bool`
