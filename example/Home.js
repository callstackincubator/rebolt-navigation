'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Text$BsReactNative = require("bs-react-native/src/components/text.js");
var View$BsReactNative = require("bs-react-native/src/components/view.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");
var NavigationConfig$RerouteNative = require("./NavigationConfig.js");
var TouchableOpacity$BsReactNative = require("bs-react-native/src/components/touchableOpacity.js");

var component = ReasonReact.statelessComponent("Home");

var continer = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1),
      /* :: */[
        Style$BsReactNative.justifyContent(/* Center */2),
        /* :: */[
          Style$BsReactNative.alignItems(/* Center */2),
          /* [] */0
        ]
      ]
    ]);

function button(color) {
  return Style$BsReactNative.style(/* :: */[
              Style$BsReactNative.flex(1),
              /* :: */[
                Style$BsReactNative.justifyContent(/* Center */2),
                /* :: */[
                  Style$BsReactNative.paddingHorizontal(/* Pt */Block.__(0, [20])),
                  /* :: */[
                    Style$BsReactNative.maxHeight(/* Pt */Block.__(0, [40])),
                    /* :: */[
                      Style$BsReactNative.marginTop(/* Pt */Block.__(0, [16])),
                      /* :: */[
                        Style$BsReactNative.backgroundColor(/* String */Block.__(0, [color])),
                        /* :: */[
                          Style$BsReactNative.borderRadius(20),
                          /* :: */[
                            Style$BsReactNative.width(/* Pt */Block.__(0, [100])),
                            /* [] */0
                          ]
                        ]
                      ]
                    ]
                  ]
                ]
              ]
            ]);
}

var buttonText = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.textAlign(/* Center */3),
      /* [] */0
    ]);

var title = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.fontSize(/* Float */Block.__(0, [20])),
      /* [] */0
    ]);

var Styles = /* module */[
  /* continer */continer,
  /* button */button,
  /* buttonText */buttonText,
  /* title */title
];

function renderButtons(nav) {
  return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                  ReasonReact.element(/* None */0, /* None */0, TouchableOpacity$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[button("#4cd964")], /* None */0, /* Some */[(function () {
                                  return Curry._1(nav[/* push */0], /* Admin */2);
                                })], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[buttonText], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */["Push"]))])),
                  ReasonReact.element(/* None */0, /* None */0, TouchableOpacity$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[button("#ff9500")], /* None */0, /* Some */[(function () {
                                  return Curry._1(nav[/* pop */2], /* () */0);
                                })], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[buttonText], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */["Pop"]))]))
                ]));
}

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
                              /* Some */["Home"],
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              (function () {
                                  return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[continer], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                                                  ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[title], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */["Home screen"])),
                                                  renderButtons(nav)
                                                ]));
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
exports.Styles = Styles;
exports.renderButtons = renderButtons;
exports.make = make;
/* component Not a pure module */
