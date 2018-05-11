'use strict';

var ReRoute$RerouteNative = require("../src/ReRoute.js");

var Config = /* module */[];

var include = ReRoute$RerouteNative.CreateNavigation(Config);

var StackNavigator = include[0];

var TabNavigator = include[1];

exports.Config = Config;
exports.StackNavigator = StackNavigator;
exports.TabNavigator = TabNavigator;
/* include Not a pure module */
