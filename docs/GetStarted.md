---
id: get-started
title: Get Started
sidebar_label: Quick start
---

The library is built in Reason, so we are assuming you are all set with the Reason configuration, if not please check out [Reason docs](https://reasonml.github.io) to learn how to get started with Reason.

## Install the library

```sh
yarn add rebolt-navigation
# or
npm install rebolt-navigation --save
```

## Add it to your config

In your `bsconfig.json` add it to the dependecies:

```json
"bs-dependencies": [
  "reason-react",
  "rebolt-navigation"
],
"namespace": true
```

### Peer dependencies

In addition you will need to install a few peer dependencies:

* `react-native-gesture-handler` - [installation instructions](https://github.com/kmagiera/react-native-gesture-handler#installation)
* `bs-react-native` - `^0.8.0`

## Usage

First we need to create the navigation based on our needs.
In `Navigation.re`, we will create our `Config` module and pass it to a `CreateNavigation` functor:

**Navigation.re**:

```reason
module Config = {
  type route =
    | Home
    | About
    | Contact;
};

include RerouteNative.Rebolt Navigation.CreateNavigation(Config);
```

That's it! Now you are ready to use Rebolt Navigation in your React Native application.
