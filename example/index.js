import { app } from "../lib/js/example/re/App.js";
import React from "react";
import { AppRegistry } from "react-native";

console.ignoredYellowBox = ["Warning: component"];

AppRegistry.registerComponent("ReasonDemo", () => app);
