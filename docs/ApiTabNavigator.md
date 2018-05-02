---
id: api-tab-navigator
title: Tab Navigator
sidebar_label: Tab Navigator
---

## Props

* `~initialRoute`: `Config.RouteName` see [Config](get-started.html#usage),
* `~routes`: `array([Config.route](get-started.html#usage))` see ,
* `~navigation`: Navigation instance
* `~headerMode?`: `headerMode`,

## Screen

### Props

* `~navigation`: Navigation instance,
* `~label`: `string`,
* `~isActive`: `bool`

## TabBar

### Props

* `~tabBarProps`: [tabBarProps](get-started.html#tabbarprops)

## TabBarItem

### Props

* `~navigation`: Navigation instance,
* `~label`: `string`,
* `~isActive`: `bool`

## Types

### TabBarProps

* `screens`: `array([screenConfig](get-started.html#screenconfig))`
* `currentRoute`: [Config.route](get-started.html#usage)
* `jumpTo`,

### screenConfig

* `route`: [Config.route](get-started.html#usage),
* `label`: `string`,
