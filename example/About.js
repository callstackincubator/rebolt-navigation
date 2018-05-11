'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Text$BsReactNative = require("bs-react-native/src/components/text.js");
var View$BsReactNative = require("bs-react-native/src/components/view.js");
var Image$BsReactNative = require("bs-react-native/src/components/image.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");
var NavigationConfig$RerouteNative = require("./NavigationConfig.js");

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

var Styles = /* module */[/* container */container];

var component = ReasonReact.statelessComponent("About");

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
              return ReasonReact.element(/* None */0, /* None */0, Curry._3(NavigationConfig$RerouteNative.TabNavigator[/* Screen */1][/* make */0], navigation, (function (param) {
                                return ReasonReact.element(/* None */0, /* None */0, Curry._4(NavigationConfig$RerouteNative.TabNavigator[/* TabBar */2][/* Item */0][/* make */0], "", /* Some */[param[/* isActive */0] ? /* URI */Block.__(0, [Image$BsReactNative.imageURISource("https://png.icons8.com/ios/1600/like.png", /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* () */0)]) : /* URI */Block.__(0, [Image$BsReactNative.imageURISource("https://png.icons8.com/ios/1600/settings.png", /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* () */0)])], /* None */0, /* array */[]));
                              }), (function () {
                                return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[Style$BsReactNative.style(/* :: */[
                                                                Style$BsReactNative.fontSize(/* Float */Block.__(0, [24])),
                                                                /* [] */0
                                                              ])], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */["About"]))]));
                              })));
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
/* container Not a pure module */
