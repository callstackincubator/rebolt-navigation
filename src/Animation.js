'use strict';

var List = require("bs-platform/lib/js/list.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");
var Animated$BsReactNative = require("bs-react-native/src/animated.js");
var Platform$BsReactNative = require("bs-react-native/src/platform.js");
var Dimensions$BsReactNative = require("bs-react-native/src/dimensions.js");

var func = Animated$BsReactNative.Value[/* Spring */20][/* animate */0];

function slideHorizontal_000(param) {
  var func$1 = Curry._1(func, param);
  return (function (param) {
      return Curry.app(func$1, [
                  param,
                  /* None */0,
                  /* None */0,
                  /* None */0,
                  /* None */0,
                  /* None */0,
                  /* None */0,
                  /* None */0,
                  /* None */0,
                  /* Some */[1000.0],
                  /* Some */[3.0],
                  /* Some */[500.0],
                  /* None */0,
                  /* Some */[true],
                  /* None */0,
                  /* None */0,
                  /* () */0
                ]);
    });
}

function slideHorizontal_001(value) {
  var screenWidth = Dimensions$BsReactNative.get(/* window */-762539024).width;
  return Style$BsReactNative.style(/* :: */[
              Style$BsReactNative.opacity(/* Interpolated */Block.__(2, [Curry._8(Animated$BsReactNative.Value[/* interpolate */10], value, /* :: */[
                            -1.0,
                            /* :: */[
                              -0.99,
                              /* :: */[
                                0.0,
                                /* :: */[
                                  0.99,
                                  /* :: */[
                                    1.0,
                                    /* [] */0
                                  ]
                                ]
                              ]
                            ]
                          ], /* `float */[
                            43435420,
                            /* :: */[
                              0.0,
                              /* :: */[
                                1.0,
                                /* :: */[
                                  1.0,
                                  /* :: */[
                                    0.85,
                                    /* :: */[
                                      0.0,
                                      /* [] */0
                                    ]
                                  ]
                                ]
                              ]
                            ]
                          ], /* None */0, /* None */0, /* None */0, /* None */0, /* () */0)])),
              /* :: */[
                Style$BsReactNative.Transform[/* makeInterpolated */2](/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[Curry._8(Animated$BsReactNative.Value[/* interpolate */10], value, List.map((function (prim) {
                                  return prim;
                                }), /* :: */[
                                -1,
                                /* :: */[
                                  0,
                                  /* :: */[
                                    1,
                                    /* [] */0
                                  ]
                                ]
                              ]), /* `float */[
                            43435420,
                            /* :: */[
                              -screenWidth * 0.3,
                              /* :: */[
                                0.0,
                                /* :: */[
                                  screenWidth,
                                  /* [] */0
                                ]
                              ]
                            ]
                          ], /* None */0, /* None */0, /* None */0, /* None */0, /* () */0)], /* None */0, /* None */0, /* None */0, /* () */0),
                /* [] */0
              ]
            ]);
}

function slideHorizontal_002() {
  return Style$BsReactNative.style(/* [] */0);
}

var slideHorizontal = /* record */[
  slideHorizontal_000,
  slideHorizontal_001,
  slideHorizontal_002
];

var func$1 = Animated$BsReactNative.Value[/* Timing */19][/* animate */0];

var arg = /* Some */[(function (t) {
      return Math.pow(t, 5.0);
    })];

function fadeVertical_000(param) {
  var func$2 = Curry._1(func$1, param);
  return (function (param) {
      return Curry.app(func$2, [
                  param,
                  arg,
                  /* Some */[350.0],
                  /* None */0,
                  /* None */0,
                  /* Some */[true],
                  /* None */0,
                  /* None */0,
                  /* () */0
                ]);
    });
}

function fadeVertical_001(value) {
  return Style$BsReactNative.style(/* :: */[
              Style$BsReactNative.opacity(/* Interpolated */Block.__(2, [Curry._8(Animated$BsReactNative.Value[/* interpolate */10], value, /* :: */[
                            -1.0,
                            /* :: */[
                              -0.99,
                              /* :: */[
                                0.0,
                                /* :: */[
                                  1.0,
                                  /* [] */0
                                ]
                              ]
                            ]
                          ], /* `float */[
                            43435420,
                            /* :: */[
                              0.0,
                              /* :: */[
                                1.0,
                                /* :: */[
                                  1.0,
                                  /* :: */[
                                    0.0,
                                    /* [] */0
                                  ]
                                ]
                              ]
                            ]
                          ], /* None */0, /* None */0, /* None */0, /* None */0, /* () */0)])),
              /* :: */[
                Style$BsReactNative.Transform[/* makeInterpolated */2](/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[Curry._8(Animated$BsReactNative.Value[/* interpolate */10], value, /* :: */[
                            -1.0,
                            /* :: */[
                              -0.99,
                              /* :: */[
                                0.0,
                                /* :: */[
                                  1.0,
                                  /* [] */0
                                ]
                              ]
                            ]
                          ], /* `float */[
                            43435420,
                            /* :: */[
                              0.0,
                              /* :: */[
                                0.0,
                                /* :: */[
                                  0.0,
                                  /* :: */[
                                    50.0,
                                    /* [] */0
                                  ]
                                ]
                              ]
                            ]
                          ], /* None */0, /* None */0, /* None */0, /* None */0, /* () */0)], /* None */0, /* None */0, /* () */0),
                /* [] */0
              ]
            ]);
}

function fadeVertical_002() {
  return Style$BsReactNative.style(/* [] */0);
}

var fadeVertical = /* record */[
  fadeVertical_000,
  fadeVertical_001,
  fadeVertical_002
];

var match = Platform$BsReactNative.os(/* () */0);

var $$default = match ? slideHorizontal : fadeVertical;

var func$2 = Animated$BsReactNative.Value[/* Timing */19][/* animate */0];

function none_000(param) {
  var func$3 = Curry._1(func$2, param);
  return (function (param) {
      return Curry.app(func$3, [
                  param,
                  /* None */0,
                  /* Some */[0.0],
                  /* None */0,
                  /* None */0,
                  /* Some */[true],
                  /* None */0,
                  /* None */0,
                  /* () */0
                ]);
    });
}

var none_001 = /* forCard */$$default[/* forCard */1];

var none_002 = /* forHeader */$$default[/* forHeader */2];

var none = /* record */[
  none_000,
  none_001,
  none_002
];

exports.slideHorizontal = slideHorizontal;
exports.fadeVertical = fadeVertical;
exports.$$default = $$default;
exports.default = $$default;
exports.__esModule = true;
exports.none = none;
/* match Not a pure module */
