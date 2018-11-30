# ReRoute

[![Build Status][build-badge]][build]
[![Version][version-badge]][package]
[![MIT License][license-badge]][license]
[![PRs Welcome][prs-welcome-badge]][prs-welcome]
[![Chat][chat-badge]][chat]

> a fast, declarative navigation for react native

We're looking forward to seeing your feedback or questions on Discord

### Installation

Open a Terminal in your project's folder and run,

```she
yarn add reroute-native
```

After installation, you will need to add this library to your `bsconfig.json` dependencies

```json
"bs-dependencies": [
  "reason-react",
  "reroute"
],
```

In addition you will need to install a peer dependencies:

```sh
yarn add react-native-gesture-handler
react-native link react-native-gesture-handler
```

You can find additional [installation instructions](https://github.com/kmagiera/react-native-gesture-handler#installation) here.

## Examples
- example built-in library - [/example](/example)

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

<!-- badges -->
[build-badge]: https://img.shields.io/circleci/project/github/callstackincubator/rebolt-navigation/master.svg?style=flat-square
[build]: https://circleci.com/gh/callstackincubator/rebolt-navigation
[version-badge]: https://img.shields.io/npm/v/rebolt-navigation.svg?style=flat-square
[package]: https://www.npmjs.com/package/rebolt-navigation
[license-badge]: https://img.shields.io/npm/l/rebolt-navigation.svg?style=flat-square
[license]: https://opensource.org/licenses/MIT
[prs-welcome-badge]: https://img.shields.io/badge/PRs-welcome-brightgreen.svg?style=flat-square
[prs-welcome]: http://makeapullrequest.com
[chat-badge]: https://img.shields.io/discord/426714625279524876.svg?style=flat-square&colorB=758ED3
[chat]: https://discord.gg/zwR2Cdh
