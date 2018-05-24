# ReRoute Native

> a fast, declarative navigation for react native

We're looking forward to seeing your feedback or questions on Discord

![Discord](https://img.shields.io/discord/426714625279524876.svg)

## Getting started

[ReRoute Native website](https://reroute-native.netlify.com/)

### Installation

Open a Terminal in your project's folder and run,

```
$ yarn add reroute-native
```

After installation, you will need to add this library to your `bsconfig.json` dependencies

```
"bs-dependencies": [
  "reason-react",
  "reroute-native"
],
```

In addition you will need to install a few peer dependencies:

* `react-native-gesture-handler` - [installation instructions](https://github.com/kmagiera/react-native-gesture-handler#installation)
* `bs-react-native` - `^0.7.0-beta`

## Usage

[View the docs](https://reroute-native.netlify.com/docs/get-started.html#usage)

## Developing

```
# Starts Metro (React Native Packager)
$ npm run start-example

# Runs the app on iOS/Android
$ npm run run-ios

# Watches for source build changes
$ npm start
```

## License

MIT (c) 2018 Callstack
