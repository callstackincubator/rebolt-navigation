'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");
var Animated$BsReactNative = require("bs-react-native/src/animated.js");
var Caml_builtin_exceptions = require("bs-platform/lib/js/caml_builtin_exceptions.js");
var Dimensions$BsReactNative = require("bs-react-native/src/dimensions.js");

function crossFadeInterpolation(param) {
  var exit = 0;
  if (param) {
    var match = param[1];
    if (match) {
      var match$1 = match[1];
      if (match$1 && !match$1[1]) {
        var end_ = match$1[0];
        var mid = match[0];
        var start = param[0];
        return (function (value) {
            return Curry._8(Animated$BsReactNative.Value[/* interpolate */10], value, /* :: */[
                        start,
                        /* :: */[
                          start + 0.001,
                          /* :: */[
                            mid - 0.9,
                            /* :: */[
                              mid - 0.2,
                              /* :: */[
                                mid,
                                /* :: */[
                                  end_ - 0.001,
                                  /* :: */[
                                    end_,
                                    /* [] */0
                                  ]
                                ]
                              ]
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
                                0.3,
                                /* :: */[
                                  1.0,
                                  /* :: */[
                                    0.0,
                                    /* :: */[
                                      0.0,
                                      /* [] */0
                                    ]
                                  ]
                                ]
                              ]
                            ]
                          ]
                        ]
                      ], /* None */0, /* None */0, /* None */0, /* None */0, /* () */0);
          });
      } else {
        exit = 1;
      }
    } else {
      exit = 1;
    }
  } else {
    exit = 1;
  }
  if (exit === 1) {
    throw [
          Caml_builtin_exceptions.match_failure,
          [
            "HeaderInterpolator.re",
            13,
            29
          ]
        ];
  }
  
}

function floating_000(value) {
  var offset = ((Dimensions$BsReactNative.get(/* window */-762539024).width / 2 | 0) - 70 | 0) + 25 | 0;
  return Style$BsReactNative.style(/* :: */[
              Style$BsReactNative.opacity(/* Interpolated */Block.__(2, [Curry._8(Animated$BsReactNative.Value[/* interpolate */10], value, /* :: */[
                            -1.0,
                            /* :: */[
                              -0.999,
                              /* :: */[
                                -0.5,
                                /* :: */[
                                  0.0,
                                  /* :: */[
                                    0.7,
                                    /* :: */[
                                      0.999,
                                      /* :: */[
                                        1.0,
                                        /* [] */0
                                      ]
                                    ]
                                  ]
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
                                    1.0,
                                    /* :: */[
                                      0.0,
                                      /* :: */[
                                        0.0,
                                        /* :: */[
                                          0.0,
                                          /* [] */0
                                        ]
                                      ]
                                    ]
                                  ]
                                ]
                              ]
                            ]
                          ], /* None */0, /* None */0, /* None */0, /* None */0, /* () */0)])),
              /* :: */[
                Style$BsReactNative.Transform[/* makeInterpolated */2](/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[Curry._8(Animated$BsReactNative.Value[/* interpolate */10], value, /* :: */[
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
                              offset,
                              /* :: */[
                                offset,
                                /* :: */[
                                  0.0,
                                  /* :: */[
                                    -offset,
                                    /* :: */[
                                      -offset,
                                      /* [] */0
                                    ]
                                  ]
                                ]
                              ]
                            ]
                          ], /* None */0, /* None */0, /* None */0, /* None */0, /* () */0)], /* None */0, /* None */0, /* None */0, /* () */0),
                /* [] */0
              ]
            ]);
}

function floating_001() {
  return Style$BsReactNative.style(/* [] */0);
}

function floating_002(value) {
  var offset = ((Dimensions$BsReactNative.get(/* window */-762539024).width / 2 | 0) - 70 | 0) + 25 | 0;
  return Style$BsReactNative.style(/* :: */[
              Style$BsReactNative.opacity(/* Interpolated */Block.__(2, [Curry._8(Animated$BsReactNative.Value[/* interpolate */10], value, /* :: */[
                            -1.0,
                            /* :: */[
                              -0.999,
                              /* :: */[
                                -0.35,
                                /* :: */[
                                  0.0,
                                  /* :: */[
                                    0.5,
                                    /* :: */[
                                      0.999,
                                      /* :: */[
                                        1.0,
                                        /* [] */0
                                      ]
                                    ]
                                  ]
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
                                    1.0,
                                    /* :: */[
                                      0.5,
                                      /* :: */[
                                        0.0,
                                        /* :: */[
                                          0.0,
                                          /* [] */0
                                        ]
                                      ]
                                    ]
                                  ]
                                ]
                              ]
                            ]
                          ], /* None */0, /* None */0, /* None */0, /* None */0, /* () */0)])),
              /* :: */[
                Style$BsReactNative.Transform[/* makeInterpolated */2](/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[Curry._8(Animated$BsReactNative.Value[/* interpolate */10], value, /* :: */[
                            -1.0,
                            /* :: */[
                              -0.999,
                              /* :: */[
                                0.0,
                                /* :: */[
                                  0.999,
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
                              offset,
                              /* :: */[
                                offset,
                                /* :: */[
                                  0.0,
                                  /* :: */[
                                    -offset * 1.5,
                                    /* :: */[
                                      -offset * 1.5,
                                      /* [] */0
                                    ]
                                  ]
                                ]
                              ]
                            ]
                          ], /* None */0, /* None */0, /* None */0, /* None */0, /* () */0)], /* None */0, /* None */0, /* None */0, /* () */0),
                /* [] */0
              ]
            ]);
}

function floating_003(value) {
  return Style$BsReactNative.style(/* :: */[
              Style$BsReactNative.opacity(/* Interpolated */Block.__(2, [Curry._8(Animated$BsReactNative.Value[/* interpolate */10], value, /* :: */[
                            -1.0,
                            /* :: */[
                              -0.999,
                              /* :: */[
                                -0.5,
                                /* :: */[
                                  0.0,
                                  /* :: */[
                                    0.5,
                                    /* :: */[
                                      0.999,
                                      /* :: */[
                                        1.0,
                                        /* [] */0
                                      ]
                                    ]
                                  ]
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
                                  0.7,
                                  /* :: */[
                                    1.0,
                                    /* :: */[
                                      0.7,
                                      /* :: */[
                                        0.0,
                                        /* :: */[
                                          0.0,
                                          /* [] */0
                                        ]
                                      ]
                                    ]
                                  ]
                                ]
                              ]
                            ]
                          ], /* None */0, /* None */0, /* None */0, /* None */0, /* () */0)])),
              /* [] */0
            ]);
}

function floating_004(value) {
  return Style$BsReactNative.style(/* :: */[
              Style$BsReactNative.opacity(/* Interpolated */Block.__(2, [Curry._1(crossFadeInterpolation(/* :: */[
                                -1.0,
                                /* :: */[
                                  0.0,
                                  /* :: */[
                                    1.0,
                                    /* [] */0
                                  ]
                                ]
                              ]), value)])),
              /* [] */0
            ]);
}

var floating = /* record */[
  floating_000,
  floating_001,
  floating_002,
  floating_003,
  floating_004
];

exports.floating = floating;
/* Animated-BsReactNative Not a pure module */
