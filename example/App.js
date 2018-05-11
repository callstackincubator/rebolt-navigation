'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Home$RerouteNative = require("./Home.js");
var Admin$RerouteNative = require("./Admin.js");
var Welcome$RerouteNative = require("./Welcome.js");
var TabExample$RerouteNative = require("./TabExample.js");
var UserProfile$RerouteNative = require("./UserProfile.js");
var AsyncStorage$BsReactNative = require("bs-react-native/src/asyncStorage.js");
var NavigationConfig$RerouteNative = require("./NavigationConfig.js");
var CustomTabBarExample$RerouteNative = require("./CustomTabBarExample.js");

var component = ReasonReact.statelessComponent("Main");

function make() {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */component[/* didMount */4],
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */component[/* willUnmount */6],
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function () {
              return ReasonReact.element(/* None */0, /* None */0, Curry._5(NavigationConfig$RerouteNative.StackNavigator[/* make */1], /* array */[/* Welcome */0], /* Some */[(function (state) {
                                  AsyncStorage$BsReactNative.setItem("$state", JSON.stringify(Curry._1(NavigationConfig$RerouteNative.StackNavigator[/* Persistence */0][/* encode */0], state)), /* None */0, /* () */0);
                                  return /* () */0;
                                })], /* None */0, /* None */0, (function (currentRoute, navigation) {
                                var exit = 0;
                                switch (currentRoute) {
                                  case 0 : 
                                      return ReasonReact.element(/* None */0, /* None */0, Welcome$RerouteNative.make(navigation, /* array */[]));
                                  case 2 : 
                                      return ReasonReact.element(/* None */0, /* None */0, Admin$RerouteNative.make(navigation, /* array */[]));
                                  case 4 : 
                                      return ReasonReact.element(/* None */0, /* None */0, Home$RerouteNative.make(navigation, /* array */[]));
                                  case 5 : 
                                      return ReasonReact.element(/* None */0, /* None */0, UserProfile$RerouteNative.make(navigation, /* array */[]));
                                  case 7 : 
                                      return ReasonReact.element(/* None */0, /* None */0, TabExample$RerouteNative.make(navigation, /* array */[]));
                                  case 1 : 
                                  case 3 : 
                                  case 6 : 
                                  case 8 : 
                                  case 9 : 
                                      exit = 1;
                                      break;
                                  case 10 : 
                                      return ReasonReact.element(/* None */0, /* None */0, CustomTabBarExample$RerouteNative.make(navigation, /* array */[]));
                                  
                                }
                                if (exit === 1) {
                                  return ReasonReact.element(/* None */0, /* None */0, TabExample$RerouteNative.make(navigation, /* array */[]));
                                }
                                
                              })));
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

var Main = /* module */[
  /* component */component,
  /* make */make
];

function app() {
  return ReasonReact.element(/* None */0, /* None */0, make(/* array */[]));
}

exports.Main = Main;
exports.app = app;
/* component Not a pure module */
