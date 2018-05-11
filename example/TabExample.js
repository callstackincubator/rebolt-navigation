'use strict';

var Curry = require("bs-platform/lib/js/curry.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Messages$RerouteNative = require("./Messages.js");
var Settings$RerouteNative = require("./Settings.js");
var ContactList$RerouteNative = require("./ContactList.js");
var NavigationConfig$RerouteNative = require("./NavigationConfig.js");

var component = ReasonReact.statelessComponent("Profile");

function make(nav, _) {
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
              return ReasonReact.element(/* None */0, /* None */0, Curry.app(NavigationConfig$RerouteNative.StackNavigator[/* Screen */3][/* make */0], [
                              nav,
                              /* None */0,
                              /* Some */["Profile"],
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              (function () {
                                  return ReasonReact.element(/* None */0, /* None */0, Curry._6(NavigationConfig$RerouteNative.TabNavigator[/* make */0], /* ContactList */8, /* array */[
                                                  /* ContactList */8,
                                                  /* Messages */9,
                                                  /* About */6
                                                ], /* None */0, /* None */0, /* None */0, (function (navigation) {
                                                    var match = navigation[/* currentRoute */1];
                                                    var exit = 0;
                                                    if (match >= 8) {
                                                      switch (match - 8 | 0) {
                                                        case 0 : 
                                                            return ReasonReact.element(/* None */0, /* None */0, ContactList$RerouteNative.make(navigation, nav, false, /* array */[]));
                                                        case 1 : 
                                                            return ReasonReact.element(/* None */0, /* None */0, Messages$RerouteNative.make(navigation, false, /* array */[]));
                                                        case 2 : 
                                                            exit = 1;
                                                            break;
                                                        
                                                      }
                                                    } else {
                                                      exit = 1;
                                                    }
                                                    if (exit === 1) {
                                                      return ReasonReact.element(/* None */0, /* None */0, Settings$RerouteNative.make(navigation, nav, /* array */[]));
                                                    }
                                                    
                                                  })));
                                })
                            ]));
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

exports.component = component;
exports.make = make;
/* component Not a pure module */
