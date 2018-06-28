# Rebolt Navigation

[![CircleCI](https://circleci.com/gh/callstackincubator/rebolt-navigation.svg?style=svg)](https://circleci.com/gh/callstackincubator/rebolt-navigation)

> a fast, declarative navigation for react native

We're looking forward to seeing your feedback or questions on Discord

[![Discord](https://img.shields.io/discord/426714625279524876.svg)](https://discord.gg/8DW7b4N)


## Getting started

[Rebolt Navigation website](https://rebolt-navigation.callstack.com/)

### Installation

Open a Terminal in your project's folder and run,

```she
yarn add rebolt-navigation
```

After installation, you will need to add this library to your `bsconfig.json` dependencies

```json
"bs-dependencies": [
  "reason-react",
  "rebolt-navigation"
],
```

In addition you will need to install a few peer dependencies:

```sh
yarn add bs-react-native react-native-gesture-handler
```

* `react-native-gesture-handler` - [installation instructions](https://github.com/kmagiera/react-native-gesture-handler#installation)
* `bs-react-native` - `^0.8.0`

As per [this issue](https://github.com/callstackincubator/rebolt-navigation/issues/103), you might need to add the following to your `bsconfig.json`:

```

"package-specs": {
  "module": "commonjs",
  "in-source": true
}

```
This generates output alongside source files. ([documentation](https://bucklescript.github.io/docs/en/build-configuration.html#package-specs))


## Usage

[View the docs](https://rebolt-navigation.callstack.com/docs/get-started.html#usage)

## Examples
- example built-in library - [/example](/example)
- standalone example - [reroute-example](https://github.com/souhe/reroute-example)

## Developing

```sh
# Starts Metro (React Native Packager)
npm run start-example

# Runs the app on iOS/Android
npm run run-ios

# Watches for source build changes
npm start
```

## License

MIT (c) 2018 Callstack
