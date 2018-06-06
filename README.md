# ReRoute Native

[![CircleCI](https://circleci.com/gh/callstack/reroute-native.svg?style=svg)](https://circleci.com/gh/callstack/reroute-native)

> a fast, declarative navigation for react native

We're looking forward to seeing your feedback or questions on Discord

[![Discord](https://img.shields.io/discord/426714625279524876.svg)](https://discord.gg/8DW7b4N)


## Getting started

[ReRoute Native website](https://reroute-native.netlify.com/)

### Installation

Open a Terminal in your project's folder and run,

```she
yarn add reroute-native
```

After installation, you will need to add this library to your `bsconfig.json` dependencies

```json
"bs-dependencies": [
  "reason-react",
  "reroute-native"
],
```

Then, as per [this issue](https://github.com/callstack/reroute-native/issues/103), you might need to add the following to your `bsconfig`:

```

"package-specs": {
  "in-source": true
}

```
If you are curious what the above does, you can find the [documentation](https://bucklescript.github.io/docs/en/build-configuration.html#package-specs) here.


In addition you will need to install a few peer dependencies:

```sh
yarn add bs-react-native react-native-gesture-handler
```

* `react-native-gesture-handler` - [installation instructions](https://github.com/kmagiera/react-native-gesture-handler#installation)
* `bs-react-native` - `^0.8.0`

## Usage

[View the docs](https://reroute-native.netlify.com/docs/get-started.html#usage)

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
