'use strict';

var TabNavigator$RerouteNative = require("./TabNavigator.js");
var StackNavigator$RerouteNative = require("./StackNavigator.js");

function CreateNavigation(Config) {
  var include = StackNavigator$RerouteNative.CreateStackNavigator(Config);
  var include$1 = TabNavigator$RerouteNative.CreateTabNavigator(Config);
  return /* module */[
          /* StackNavigator */include[0],
          /* TabNavigator */include$1[0]
        ];
}

exports.CreateNavigation = CreateNavigation;
/* TabNavigator-RerouteNative Not a pure module */
