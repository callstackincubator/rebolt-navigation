'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var View$BsReactNative = require("bs-react-native/src/components/view.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");
var TouchableOpacity$BsReactNative = require("bs-react-native/src/components/touchableOpacity.js");

var tabBar = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1),
      /* :: */[
        Style$BsReactNative.flexDirection(/* Row */0),
        /* :: */[
          Style$BsReactNative.justifyContent(/* SpaceBetween */5),
          /* :: */[
            Style$BsReactNative.position(/* Absolute */0),
            /* :: */[
              Style$BsReactNative.top(/* Pt */Block.__(0, [0])),
              /* :: */[
                Style$BsReactNative.left(/* Pt */Block.__(0, [0])),
                /* :: */[
                  Style$BsReactNative.right(/* Pt */Block.__(0, [0])),
                  /* :: */[
                    Style$BsReactNative.height(/* Pt */Block.__(0, [80])),
                    /* [] */0
                  ]
                ]
              ]
            ]
          ]
        ]
      ]
    ]);

function tabBarItem(isActive) {
  return Style$BsReactNative.style(/* :: */[
              Style$BsReactNative.flex(1),
              /* :: */[
                Style$BsReactNative.justifyContent(/* Center */2),
                /* :: */[
                  Style$BsReactNative.alignItems(/* Center */2),
                  /* :: */[
                    Style$BsReactNative.backgroundColor(isActive ? /* String */Block.__(0, ["tomato"]) : /* String */Block.__(0, ["transparent"])),
                    /* [] */0
                  ]
                ]
              ]
            ]);
}

function tabBarItemText(isActive) {
  return Style$BsReactNative.style(/* :: */[
              Style$BsReactNative.color(isActive ? /* String */Block.__(0, ["white"]) : /* String */Block.__(0, ["tomato"])),
              /* [] */0
            ]);
}

var Styles = /* module */[
  /* tabBar */tabBar,
  /* tabBarItem */tabBarItem,
  /* tabBarItemText */tabBarItemText
];

var component = ReasonReact.statelessComponent("CustomTabBar");

function make(tabBarProps, _) {
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
              return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[tabBar], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[$$Array.mapi((function (index, screen) {
                                      var isActive = tabBarProps[/* currentRoute */1] === screen[/* route */0];
                                      return ReasonReact.element(/* Some */[String(index)], /* None */0, TouchableOpacity$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[tabBarItem(isActive)], /* None */0, /* Some */[(function () {
                                                            return Curry._1(tabBarProps[/* jumpTo */2], screen[/* route */0]);
                                                          })], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[Curry._1(screen[/* tabItem */1], /* record */[/* isActive */isActive])]));
                                    }), tabBarProps[/* screens */0])]));
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

exports.Styles = Styles;
exports.component = component;
exports.make = make;
/* tabBar Not a pure module */
