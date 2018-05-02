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
* `~label`: `string`
* `~isActive`: `bool`

## TabBar

### Props

* `~tabBarProps`: [tabBarProps](api-tab-navigator.html#tabbarprops)

## TabBarItem

### Props

* `~navigation`: Navigation instance
* `~label`: `string`
* `~isActive`: `bool`

## Types

### TabBarProps

* `screens`: array([screenConfig](api-tab-navigator.html#screenconfig))
* `currentRoute`: [Config.route](get-started.html#usage)
* `jumpTo`

### screenConfig

* `route`: [Config.route](get-started.html#usage)
* `label`: `string`
