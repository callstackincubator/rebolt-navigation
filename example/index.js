import { app } from "./lib/js/re/App.js";
import React from "react";
import { AppRegistry } from "react-native";

console.ignoredYellowBox = ["Warning: component"];

AppRegistry.registerComponent("ReasonDemo", () => app);
