'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Js_option = require("bs-platform/lib/js/js_option.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Js_undefined = require("bs-platform/lib/js/js_undefined.js");
var ReactNative = require("react-native");
var Text$BsReactNative = require("bs-react-native/src/components/text.js");
var View$BsReactNative = require("bs-react-native/src/components/view.js");
var Image$BsReactNative = require("bs-react-native/src/components/image.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");
var Utils$RerouteNative = require("./private/Utils.js");
var RNEvent$BsReactNative = require("bs-react-native/src/RNEvent.js");
var Animated$BsReactNative = require("bs-react-native/src/animated.js");
var Platform$BsReactNative = require("bs-react-native/src/platform.js");
var Caml_builtin_exceptions = require("bs-platform/lib/js/caml_builtin_exceptions.js");
var Dimensions$BsReactNative = require("bs-react-native/src/dimensions.js");
var StyleSheet$BsReactNative = require("bs-react-native/src/styleSheet.js");
var SafeAreaView$BsReactNative = require("bs-react-native/src/components/safeAreaView.js");
var AnimatedUtils$RerouteNative = require("./private/AnimatedUtils.js");
var TouchableOpacity$BsReactNative = require("bs-react-native/src/components/touchableOpacity.js");
var AnimatedComponents$BsReactNative = require("bs-react-native/src/components/animatedComponents.js");
var HeaderInterpolator$RerouteNative = require("./HeaderInterpolator.js");

function scr(p) {
  return Caml_array.caml_array_get(p[/* screens */0], p[/* activeScreen */1]);
}

function make(maskElement, pointerEvents, style, children) {
  return ReasonReact.wrapJsForReason(ReactNative.MaskedViewIOS, {
              maskElement: maskElement,
              pointerEvents: pointerEvents,
              style: style
            }, children);
}

function make$1(onPress, style, background, children) {
  return ReasonReact.wrapJsForReason(ReactNative.TouchableNativeFeedback, {
              onPress: Js_undefined.fromOption(onPress),
              background: Js_undefined.fromOption(background),
              style: Js_undefined.fromOption(style)
            }, ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(children)));
}

var component = ReasonReact.statelessComponent("TouchableItem");

function make$2($staropt$star, $staropt$star$1, $staropt$star$2, children) {
  var pressColor = $staropt$star ? $staropt$star[0] : "rgba(0, 0, 0, .32)";
  var onPress = $staropt$star$1 ? $staropt$star$1[0] : (function () {
        return /* () */0;
      });
  var borderless = $staropt$star$2 ? $staropt$star$2[0] : true;
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
              var match = Platform$BsReactNative.version(/* () */0) >= 21 && Platform$BsReactNative.os(/* () */0) === /* Android */0;
              if (match) {
                return ReasonReact.element(/* None */0, /* None */0, make$1(/* Some */[onPress], /* None */0, /* Some */[ReactNative.TouchableNativeFeedback.Ripple(pressColor, borderless)], children));
              } else {
                return ReasonReact.element(/* None */0, /* None */0, TouchableOpacity$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[onPress], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(children));
              }
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

var container = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.backgroundColor(/* String */Block.__(0, ["#fff"])),
      /* :: */[
        Style$BsReactNative.borderBottomWidth(StyleSheet$BsReactNative.hairlineWidth),
        /* :: */[
          Style$BsReactNative.borderBottomColor(/* String */Block.__(0, ["#A7A7AA"])),
          /* [] */0
        ]
      ]
    ]);

var match = Platform$BsReactNative.version(/* () */0) < 11;

var header = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.height(/* Pt */Block.__(0, [44.0])),
      /* :: */[
        Style$BsReactNative.position(/* Relative */1),
        /* :: */[
          Style$BsReactNative.marginTop(/* Pt */Block.__(0, [match ? 20.0 : 0.0])),
          /* [] */0
        ]
      ]
    ]);

var center = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.bottom(/* Pt */Block.__(0, [0.0])),
      /* :: */[
        Style$BsReactNative.top(/* Pt */Block.__(0, [0.0])),
        /* :: */[
          Style$BsReactNative.left(/* Pt */Block.__(0, [70.0])),
          /* :: */[
            Style$BsReactNative.right(/* Pt */Block.__(0, [70.0])),
            /* :: */[
              Style$BsReactNative.position(/* Absolute */0),
              /* :: */[
                Style$BsReactNative.flexDirection(/* Row */0),
                /* :: */[
                  Style$BsReactNative.justifyContent(/* Center */2),
                  /* :: */[
                    Style$BsReactNative.alignItems(/* Center */2),
                    /* [] */0
                  ]
                ]
              ]
            ]
          ]
        ]
      ]
    ]);

var headerTitle = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.fontSize(/* Float */Block.__(0, [17.0])),
      /* :: */[
        Style$BsReactNative.fontWeight(/* _700 */1056254712),
        /* :: */[
          Style$BsReactNative.textAlign(/* Center */3),
          /* :: */[
            Style$BsReactNative.marginHorizontal(/* Pt */Block.__(0, [16.0])),
            /* :: */[
              Style$BsReactNative.color(/* String */Block.__(0, ["rgba(0, 0, 0, .9)"])),
              /* [] */0
            ]
          ]
        ]
      ]
    ]);

var left = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.left(/* Pt */Block.__(0, [0.0])),
      /* :: */[
        Style$BsReactNative.top(/* Pt */Block.__(0, [0.0])),
        /* :: */[
          Style$BsReactNative.bottom(/* Pt */Block.__(0, [0.0])),
          /* :: */[
            Style$BsReactNative.position(/* Absolute */0),
            /* :: */[
              Style$BsReactNative.flexDirection(/* Row */0),
              /* :: */[
                Style$BsReactNative.alignItems(/* Center */2),
                /* [] */0
              ]
            ]
          ]
        ]
      ]
    ]);

var leftTitle = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.fontSize(/* Float */Block.__(0, [17.0])),
      /* :: */[
        Style$BsReactNative.color(/* String */Block.__(0, ["#037aff"])),
        /* [] */0
      ]
    ]);

var leftContainer = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flexDirection(/* Row */0),
      /* :: */[
        Style$BsReactNative.alignItems(/* Center */2),
        /* [] */0
      ]
    ]);

function leftIcon(withTitle) {
  return Style$BsReactNative.style(/* :: */[
              Style$BsReactNative.height(/* Pt */Block.__(0, [21.0])),
              /* :: */[
                Style$BsReactNative.width(/* Pt */Block.__(0, [12.0])),
                /* :: */[
                  Style$BsReactNative.marginLeft(/* Pt */Block.__(0, [9.0])),
                  /* :: */[
                    Style$BsReactNative.marginRight(/* Pt */Block.__(0, [withTitle ? 3.0 : 22.0])),
                    /* :: */[
                      Style$BsReactNative.marginVertical(/* Pt */Block.__(0, [12.0])),
                      /* :: */[
                        Style$BsReactNative.resizeMode(/* Contain */1),
                        /* [] */0
                      ]
                    ]
                  ]
                ]
              ]
            ]);
}

var iconMaskContainer = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1.0),
      /* :: */[
        Style$BsReactNative.flexDirection(/* Row */0),
        /* :: */[
          Style$BsReactNative.justifyContent(/* Center */2),
          /* [] */0
        ]
      ]
    ]);

var iconMask = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.height(/* Pt */Block.__(0, [21.0])),
      /* :: */[
        Style$BsReactNative.width(/* Pt */Block.__(0, [12.0])),
        /* :: */[
          Style$BsReactNative.marginLeft(/* Pt */Block.__(0, [9.0])),
          /* :: */[
            Style$BsReactNative.marginTop(/* Pt */Block.__(0, [-0.5])),
            /* :: */[
              Style$BsReactNative.alignSelf(/* Center */2),
              /* :: */[
                Style$BsReactNative.resizeMode(/* Contain */1),
                /* [] */0
              ]
            ]
          ]
        ]
      ]
    ]);

var iconMaskFillerRect = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1.0),
      /* :: */[
        Style$BsReactNative.backgroundColor(/* String */Block.__(0, ["#d8d8d8"])),
        /* :: */[
          Style$BsReactNative.marginLeft(/* Pt */Block.__(0, [-1.0])),
          /* [] */0
        ]
      ]
    ]);

var right = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.right(/* Pt */Block.__(0, [0.0])),
      /* :: */[
        Style$BsReactNative.top(/* Pt */Block.__(0, [0.0])),
        /* :: */[
          Style$BsReactNative.bottom(/* Pt */Block.__(0, [0.0])),
          /* :: */[
            Style$BsReactNative.position(/* Absolute */0),
            /* :: */[
              Style$BsReactNative.flexDirection(/* Row */0),
              /* :: */[
                Style$BsReactNative.alignItems(/* Center */2),
                /* [] */0
              ]
            ]
          ]
        ]
      ]
    ]);

var component$1 = ReasonReact.reducerComponent("FloatingHeader");

function make$3(props, _) {
  return /* record */[
          /* debugName */component$1[/* debugName */0],
          /* reactClassInternal */component$1[/* reactClassInternal */1],
          /* handedOffState */component$1[/* handedOffState */2],
          /* willReceiveProps */component$1[/* willReceiveProps */3],
          /* didMount */component$1[/* didMount */4],
          /* didUpdate */component$1[/* didUpdate */5],
          /* willUnmount */component$1[/* willUnmount */6],
          /* willUpdate */component$1[/* willUpdate */7],
          /* shouldUpdate */component$1[/* shouldUpdate */8],
          /* render */(function (self) {
              var activeScreen = props[/* activeScreen */1];
              var screens = props[/* screens */0];
              var upperBound = screens.length;
              var anim = AnimatedUtils$RerouteNative.interpolate(props[/* animatedValue */2], /* :: */[
                    0.0,
                    /* :: */[
                      upperBound,
                      /* [] */0
                    ]
                  ], /* `float */[
                    43435420,
                    /* :: */[
                      0.0,
                      /* :: */[
                        upperBound,
                        /* [] */0
                      ]
                    ]
                  ], /* None */0, /* Some */[/* Clamp */1], /* None */0, /* None */0, /* () */0);
              var mask = ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[iconMaskContainer], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                        ReasonReact.element(/* None */0, /* None */0, Image$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[/* Required */Block.__(1, [require("./assets/back-icon-mask.png")])], /* Some */[iconMask], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[])),
                        ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[iconMaskFillerRect], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[]))
                      ]));
              var renderLeft = function (p) {
                var match = scr(p);
                var key = match[/* key */2];
                var header = match[/* header */0];
                var match$1 = Utils$RerouteNative.StringMap[/* hasKey */24](key, self[/* state */1][/* leftWidths */1]);
                var match$2 = header[/* left */3];
                var tmp;
                if (match$2) {
                  tmp = Curry._1(match$2[0], p);
                } else {
                  var match$3 = p[/* activeScreen */1] === 0;
                  if (match$3) {
                    tmp = ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[]));
                  } else {
                    var match$4 = Caml_array.caml_array_get(p[/* screens */0], p[/* activeScreen */1] - 1 | 0)[/* header */0][/* title */1];
                    var tmp$1;
                    if (match$4) {
                      var backTitle = match$4[0];
                      var tmp$2;
                      try {
                        var lw = Curry._2(Utils$RerouteNative.StringMap[/* find */21], key, self[/* state */1][/* leftWidths */1]);
                        var tw = Curry._2(Utils$RerouteNative.StringMap[/* find */21], key, self[/* state */1][/* titleWidths */0]);
                        var ww = Dimensions$BsReactNative.get(/* window */-762539024).width;
                        var match$5 = lw + 20.0 >= (ww - tw) / 2.0;
                        tmp$2 = match$5 ? "Back" : backTitle;
                      }
                      catch (exn){
                        if (exn === Caml_builtin_exceptions.not_found) {
                          tmp$2 = backTitle;
                        } else {
                          throw exn;
                        }
                      }
                      tmp$1 = ReasonReact.element(/* None */0, /* None */0, Curry.app(AnimatedComponents$BsReactNative.View[/* make */0], [
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* Some */[Curry._1(HeaderInterpolator$RerouteNative.floating[/* forHeaderLeftLabel */2], p[/* animatedValue */2])],
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* array */[ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* Some */[1], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[leftTitle], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[tmp$2]))]
                              ]));
                    } else {
                      tmp$1 = null;
                    }
                    tmp = ReasonReact.element(/* None */0, /* None */0, TouchableOpacity$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[(function () {
                                    return Curry._1(p[/* pop */3], key);
                                  })], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[leftContainer], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                                        ReasonReact.element(/* None */0, /* None */0, Curry.app(AnimatedComponents$BsReactNative.View[/* make */0], [
                                                  /* None */0,
                                                  /* None */0,
                                                  /* None */0,
                                                  /* None */0,
                                                  /* None */0,
                                                  /* None */0,
                                                  /* None */0,
                                                  /* None */0,
                                                  /* None */0,
                                                  /* Some */[Curry._1(HeaderInterpolator$RerouteNative.floating[/* forHeaderLeftButton */3], p[/* animatedValue */2])],
                                                  /* None */0,
                                                  /* None */0,
                                                  /* None */0,
                                                  /* None */0,
                                                  /* None */0,
                                                  /* None */0,
                                                  /* None */0,
                                                  /* None */0,
                                                  /* None */0,
                                                  /* None */0,
                                                  /* array */[ReasonReact.element(/* None */0, /* None */0, Image$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[/* Required */Block.__(1, [require("./assets/back-icon.png")])], /* Some */[leftIcon(Js_option.isSome(header[/* title */1]))], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[]))]
                                                ])),
                                        tmp$1
                                      ]))]));
                  }
                }
                return ReasonReact.element(/* None */0, /* None */0, Curry.app(AnimatedComponents$BsReactNative.View[/* make */0], [
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* Some */[match$1 ? (function () {
                                        return /* () */0;
                                      }) : (function (e) {
                                        return Curry._1(self[/* send */3], /* SetLeftWidth */Block.__(1, [
                                                      key,
                                                      RNEvent$BsReactNative.NativeLayoutEvent[/* layout */0](e)[/* width */2]
                                                    ]));
                                      })],
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* Some */[Style$BsReactNative.concat(/* :: */[
                                        left,
                                        /* :: */[
                                          Curry._1(HeaderInterpolator$RerouteNative.floating[/* forHeaderLeft */1], p[/* animatedValue */2]),
                                          /* [] */0
                                        ]
                                      ])],
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* array */[tmp]
                              ]));
              };
              var renderCenter = function (p) {
                var match = scr(p);
                var key = match[/* key */2];
                var header = match[/* header */0];
                var containerStyle = Style$BsReactNative.concat(/* :: */[
                      center,
                      /* :: */[
                        Curry._1(HeaderInterpolator$RerouteNative.floating[/* forHeaderCenter */0], p[/* animatedValue */2]),
                        /* [] */0
                      ]
                    ]);
                var match$1 = header[/* center */2];
                return ReasonReact.element(/* None */0, /* None */0, Curry.app(AnimatedComponents$BsReactNative.View[/* make */0], [
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* Some */[(function (e) {
                                      return Curry._1(self[/* send */3], /* SetTitleWidth */Block.__(0, [
                                                    key,
                                                    RNEvent$BsReactNative.NativeLayoutEvent[/* layout */0](e)[/* width */2]
                                                  ]));
                                    })],
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* Some */[containerStyle],
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* array */[match$1 ? Curry._1(match$1[0], p) : ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* Some */[1], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[headerTitle], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[Js_option.getWithDefault("", header[/* title */1])]))]
                              ]));
              };
              var renderRight = function (p) {
                var match = scr(p)[/* header */0][/* right */4];
                return ReasonReact.element(/* None */0, /* None */0, Curry.app(AnimatedComponents$BsReactNative.View[/* make */0], [
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* Some */[Style$BsReactNative.concat(/* :: */[
                                        right,
                                        /* :: */[
                                          Curry._1(HeaderInterpolator$RerouteNative.floating[/* forHeaderRight */4], p[/* animatedValue */2]),
                                          /* [] */0
                                        ]
                                      ])],
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* None */0,
                                /* array */[match ? Curry._1(match[0], p) : null]
                              ]));
              };
              var lastIdx = screens.length - 1 | 0;
              return ReasonReact.element(/* None */0, /* None */0, Curry.app(SafeAreaView$BsReactNative.make, [
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* Some */[container],
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* None */0,
                              /* array */[ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[header], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[$$Array.mapi((function (idx, screen) {
                                                  var animatedValue = Curry._2(Animated$BsReactNative.Value[/* add */16], anim, Curry._1(Animated$BsReactNative.Value[/* create */0], -idx));
                                                  var props_000 = /* screens */props[/* screens */0];
                                                  var props_003 = /* pop */props[/* pop */3];
                                                  var props$1 = /* record */[
                                                    props_000,
                                                    /* activeScreen */idx,
                                                    /* animatedValue */animatedValue,
                                                    props_003
                                                  ];
                                                  var match = Utils$RerouteNative.StringMap[/* hasKey */24](screen[/* key */2], self[/* state */1][/* leftWidths */1]) && Utils$RerouteNative.StringMap[/* hasKey */24](screen[/* key */2], self[/* state */1][/* titleWidths */0]);
                                                  var initialOpacity = Style$BsReactNative.style(match ? /* [] */0 : /* :: */[
                                                          Style$BsReactNative.opacity(/* Float */Block.__(0, [0.0])),
                                                          /* [] */0
                                                        ]);
                                                  if ((lastIdx - idx | 0) > 2) {
                                                    return null;
                                                  } else {
                                                    var match$1 = activeScreen === idx;
                                                    return ReasonReact.element(/* Some */[screen[/* key */2]], /* None */0, make(mask, match$1 ? "box-none" : "none", Style$BsReactNative.concat(/* :: */[
                                                                        StyleSheet$BsReactNative.absoluteFill,
                                                                        /* :: */[
                                                                          Curry._1(screen[/* animation */1][/* forHeader */2], animatedValue),
                                                                          /* :: */[
                                                                            initialOpacity,
                                                                            /* [] */0
                                                                          ]
                                                                        ]
                                                                      ]), /* array */[
                                                                    renderCenter(props$1),
                                                                    renderLeft(props$1),
                                                                    renderRight(props$1)
                                                                  ]));
                                                  }
                                                }), screens)]))]
                            ]));
            }),
          /* initialState */(function () {
              return /* record */[
                      /* titleWidths */Utils$RerouteNative.StringMap[/* empty */0],
                      /* leftWidths */Utils$RerouteNative.StringMap[/* empty */0]
                    ];
            }),
          /* retainedProps */component$1[/* retainedProps */11],
          /* reducer */(function (action, state) {
              if (action.tag) {
                return /* Update */Block.__(0, [/* record */[
                            /* titleWidths */state[/* titleWidths */0],
                            /* leftWidths */Curry._3(Utils$RerouteNative.StringMap[/* add */3], action[0], action[1], state[/* leftWidths */1])
                          ]]);
              } else {
                return /* Update */Block.__(0, [/* record */[
                            /* titleWidths */Curry._3(Utils$RerouteNative.StringMap[/* add */3], action[0], action[1], state[/* titleWidths */0]),
                            /* leftWidths */state[/* leftWidths */1]
                          ]]);
              }
            }),
          /* subscriptions */component$1[/* subscriptions */13],
          /* jsElementWrapped */component$1[/* jsElementWrapped */14]
        ];
}

var component$2 = ReasonReact.statelessComponent("IOSHeader");

function make$4(p, _) {
  return /* record */[
          /* debugName */component$2[/* debugName */0],
          /* reactClassInternal */component$2[/* reactClassInternal */1],
          /* handedOffState */component$2[/* handedOffState */2],
          /* willReceiveProps */component$2[/* willReceiveProps */3],
          /* didMount */component$2[/* didMount */4],
          /* didUpdate */component$2[/* didUpdate */5],
          /* willUnmount */component$2[/* willUnmount */6],
          /* willUpdate */component$2[/* willUpdate */7],
          /* shouldUpdate */component$2[/* shouldUpdate */8],
          /* render */(function () {
              return ReasonReact.element(/* None */0, /* None */0, make$3(p, /* array */[]));
            }),
          /* initialState */component$2[/* initialState */10],
          /* retainedProps */component$2[/* retainedProps */11],
          /* reducer */component$2[/* reducer */12],
          /* subscriptions */component$2[/* subscriptions */13],
          /* jsElementWrapped */component$2[/* jsElementWrapped */14]
        ];
}

var header$1 = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.backgroundColor(/* String */Block.__(0, ["#FFF"])),
      /* :: */[
        Style$BsReactNative.shadowColor(/* String */Block.__(0, ["black"])),
        /* :: */[
          Style$BsReactNative.shadowOpacity(0.1),
          /* :: */[
            Style$BsReactNative.shadowRadius(StyleSheet$BsReactNative.hairlineWidth),
            /* :: */[
              Style$BsReactNative.shadowOffset(StyleSheet$BsReactNative.hairlineWidth, 0.0),
              /* :: */[
                Style$BsReactNative.elevation(4.0),
                /* :: */[
                  Style$BsReactNative.height(/* Pt */Block.__(0, [56.0])),
                  /* :: */[
                    Style$BsReactNative.alignItems(/* Center */2),
                    /* :: */[
                      Style$BsReactNative.flexDirection(/* Row */0),
                      /* [] */0
                    ]
                  ]
                ]
              ]
            ]
          ]
        ]
      ]
    ]);

var title = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.justifyContent(/* FlexStart */0),
      /* :: */[
        Style$BsReactNative.fontSize(/* Float */Block.__(0, [20.0])),
        /* :: */[
          Style$BsReactNative.fontWeight(/* _500 */1056155254),
          /* :: */[
            Style$BsReactNative.color(/* String */Block.__(0, ["rgba(0, 0, 0, 0.9)"])),
            /* :: */[
              Style$BsReactNative.marginHorizontal(/* Pt */Block.__(0, [16.0])),
              /* [] */0
            ]
          ]
        ]
      ]
    ]);

var icon = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.height(/* Pt */Block.__(0, [24.0])),
      /* :: */[
        Style$BsReactNative.width(/* Pt */Block.__(0, [24.0])),
        /* :: */[
          Style$BsReactNative.margin(/* Pt */Block.__(0, [16.0])),
          /* :: */[
            Style$BsReactNative.marginRight(/* Pt */Block.__(0, [0.0])),
            /* :: */[
              Style$BsReactNative.resizeMode(/* Contain */1),
              /* [] */0
            ]
          ]
        ]
      ]
    ]);

var component$3 = ReasonReact.statelessComponent("AndroidHeader");

function renderTitle(p) {
  var match = scr(p)[/* header */0][/* center */2];
  if (match) {
    return Curry._1(match[0], p);
  } else {
    return ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[title], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[Js_option.getWithDefault("", scr(p)[/* header */0][/* title */1])]));
  }
}

function renderLeft(p) {
  var match = scr(p)[/* header */0][/* left */3];
  if (match) {
    return Curry._1(match[0], p);
  } else {
    var match$1 = p[/* activeScreen */1] > 0;
    if (match$1) {
      return ReasonReact.element(/* None */0, /* None */0, make$2(/* None */0, /* Some */[(function () {
                          return Curry._1(p[/* pop */3], scr(p)[/* key */2]);
                        })], /* None */0, /* array */[ReasonReact.element(/* None */0, /* None */0, Image$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[/* Required */Block.__(1, [require("./assets/back-icon.png")])], /* Some */[icon], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[]))]));
    } else {
      return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[]));
    }
  }
}

function renderRight(p) {
  var match = scr(p)[/* header */0][/* right */4];
  if (match) {
    return Curry._1(match[0], p);
  } else {
    return null;
  }
}

function make$5(p, _) {
  return /* record */[
          /* debugName */component$3[/* debugName */0],
          /* reactClassInternal */component$3[/* reactClassInternal */1],
          /* handedOffState */component$3[/* handedOffState */2],
          /* willReceiveProps */component$3[/* willReceiveProps */3],
          /* didMount */component$3[/* didMount */4],
          /* didUpdate */component$3[/* didUpdate */5],
          /* willUnmount */component$3[/* willUnmount */6],
          /* willUpdate */component$3[/* willUpdate */7],
          /* shouldUpdate */component$3[/* shouldUpdate */8],
          /* render */(function () {
              return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[Style$BsReactNative.concat(/* :: */[
                                      header$1,
                                      /* :: */[
                                        Js_option.getWithDefault(Style$BsReactNative.style(/* [] */0), scr(p)[/* header */0][/* style */0]),
                                        /* [] */0
                                      ]
                                    ])], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                              renderLeft(p),
                              renderTitle(p),
                              renderRight(p)
                            ]));
            }),
          /* initialState */component$3[/* initialState */10],
          /* retainedProps */component$3[/* retainedProps */11],
          /* reducer */component$3[/* reducer */12],
          /* subscriptions */component$3[/* subscriptions */13],
          /* jsElementWrapped */component$3[/* jsElementWrapped */14]
        ];
}

var $$default = /* record */[
  /* style : None */0,
  /* title : None */0,
  /* center : None */0,
  /* left : None */0,
  /* right : None */0
];

var IOS = [make$4];

var Android = [make$5];

exports.$$default = $$default;
exports.default = $$default;
exports.__esModule = true;
exports.IOS = IOS;
exports.Android = Android;
/* component Not a pure module */
