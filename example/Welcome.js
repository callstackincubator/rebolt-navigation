'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Text$BsReactNative = require("bs-react-native/src/components/text.js");
var View$BsReactNative = require("bs-react-native/src/components/view.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");
var Dimensions$BsReactNative = require("bs-react-native/src/dimensions.js");
var NavigationConfig$RerouteNative = require("./NavigationConfig.js");
var TouchableOpacity$BsReactNative = require("bs-react-native/src/components/touchableOpacity.js");

var screenWidth = Dimensions$BsReactNative.get(/* screen */-950191252).width;

var container = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1),
      /* :: */[
        Style$BsReactNative.alignItems(/* Center */2),
        /* :: */[
          Style$BsReactNative.justifyContent(/* Center */2),
          /* [] */0
        ]
      ]
    ]);

function button(color) {
  return Style$BsReactNative.style(/* :: */[
              Style$BsReactNative.marginVertical(/* Pt */Block.__(0, [5])),
              /* :: */[
                Style$BsReactNative.justifyContent(/* Center */2),
                /* :: */[
                  Style$BsReactNative.alignItems(/* Center */2),
                  /* :: */[
                    Style$BsReactNative.backgroundColor(/* String */Block.__(0, [color])),
                    /* :: */[
                      Style$BsReactNative.width(/* Pt */Block.__(0, [screenWidth / 2 | 0])),
                      /* :: */[
                        Style$BsReactNative.borderRadius(25),
                        /* :: */[
                          Style$BsReactNative.paddingVertical(/* Pt */Block.__(0, [10])),
                          /* [] */0
                        ]
                      ]
                    ]
                  ]
                ]
              ]
            ]);
}

var text = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.color(/* String */Block.__(0, ["#f2f2f2"])),
      /* :: */[
        Style$BsReactNative.fontWeight(/* _600 */1056204983),
        /* :: */[
          Style$BsReactNative.fontSize(/* Float */Block.__(0, [20])),
          /* [] */0
        ]
      ]
    ]);

var Style = /* module */[
  /* container */container,
  /* button */button,
  /* text */text
];

var component = ReasonReact.statelessComponent("Welcome");

var examplesList = /* array */[
  /* Tab */0,
  /* TabCustom */1,
  /* Stack */2
];

function make(navigation, _) {
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
                              navigation,
                              /* None */0,
                              /* Some */["Examples"],
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              (function () {
                                  return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[$$Array.map((function (example) {
                                                          var route;
                                                          switch (example) {
                                                            case 0 : 
                                                                route = "Tab navigation";
                                                                break;
                                                            case 1 : 
                                                                route = "Custom TabBar";
                                                                break;
                                                            case 2 : 
                                                                route = "Stack";
                                                                break;
                                                            
                                                          }
                                                          return ReasonReact.element(/* Some */[route], /* None */0, TouchableOpacity$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[button("#5ac8fa")], /* None */0, /* Some */[(function () {
                                                                                switch (example) {
                                                                                  case 0 : 
                                                                                      return Curry._1(navigation[/* push */0], /* TabExample */7);
                                                                                  case 1 : 
                                                                                      return Curry._1(navigation[/* push */0], /* CustomTabBarExample */10);
                                                                                  case 2 : 
                                                                                      return Curry._1(navigation[/* push */0], /* Home */4);
                                                                                  
                                                                                }
                                                                              })], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[text], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[route]))]));
                                                        }), examplesList)]));
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

exports.screenWidth = screenWidth;
exports.Style = Style;
exports.component = component;
exports.examplesList = examplesList;
exports.make = make;
/* screenWidth Not a pure module */
