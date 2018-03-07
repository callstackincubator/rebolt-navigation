import { app } from "./lib/js/re/app.js";
import React from "react";
import { AppRegistry } from "react-native";

console.ignoredYellowBox = ["Warning: component"];

AppRegistry.registerComponent("ReasonDemo", () => app);
