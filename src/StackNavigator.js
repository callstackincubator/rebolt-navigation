'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Js_option = require("bs-platform/lib/js/js_option.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var View$BsReactNative = require("bs-react-native/src/components/view.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");
var Utils$RerouteNative = require("./private/Utils.js");
var Header$RerouteNative = require("./Header.js");
var Animated$BsReactNative = require("bs-react-native/src/animated.js");
var Platform$BsReactNative = require("bs-react-native/src/platform.js");
var Animation$RerouteNative = require("./Animation.js");
var Dimensions$BsReactNative = require("bs-react-native/src/dimensions.js");
var Persistence$RerouteNative = require("./Persistence.js");
var AnimatedUtils$RerouteNative = require("./private/AnimatedUtils.js");
var ReactNativeGestureHandler = require("react-native-gesture-handler");
var AnimatedComponents$BsReactNative = require("bs-react-native/src/components/animatedComponents.js");

var fill = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.position(/* Absolute */0),
      /* :: */[
        Style$BsReactNative.top(/* Pt */Block.__(0, [0.0])),
        /* :: */[
          Style$BsReactNative.left(/* Pt */Block.__(0, [0.0])),
          /* :: */[
            Style$BsReactNative.right(/* Pt */Block.__(0, [0.0])),
            /* :: */[
              Style$BsReactNative.bottom(/* Pt */Block.__(0, [0.0])),
              /* [] */0
            ]
          ]
        ]
      ]
    ]);

var flex = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1.0),
      /* [] */0
    ]);

var card = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.backgroundColor(/* String */Block.__(0, ["#E9E9EF"])),
      /* :: */[
        Style$BsReactNative.shadowColor(/* String */Block.__(0, ["black"])),
        /* :: */[
          Style$BsReactNative.shadowOffset(0.0, 0.0),
          /* :: */[
            Style$BsReactNative.shadowOpacity(0.2),
            /* :: */[
              Style$BsReactNative.shadowRadius(5.0),
              /* [] */0
            ]
          ]
        ]
      ]
    ]);

var stackContainer = Style$BsReactNative.concat(/* :: */[
      flex,
      /* :: */[
        Style$BsReactNative.style(/* :: */[
              Style$BsReactNative.flexDirection(/* ColumnReverse */3),
              /* [] */0
            ]),
        /* [] */0
      ]
    ]);

function CreateStackNavigator() {
  var include = Persistence$RerouteNative.CreatePersistence(/* module */[]);
  var make = function (onGestureEvent, maxDeltaX, enabled, onHandlerStateChange, minDeltaX, hitSlop, children) {
    return ReasonReact.wrapJsForReason(ReactNativeGestureHandler.PanGestureHandler, {
                onGestureEvent: onGestureEvent,
                onHandlerStateChange: onHandlerStateChange,
                maxDeltaX: maxDeltaX,
                minDeltaX: minDeltaX,
                enabled: enabled,
                hitSlop: hitSlop
              }, children);
  };
  var screenWidth = Dimensions$BsReactNative.get(/* window */-762539024).width;
  var animatedValue = Curry._1(Animated$BsReactNative.Value[/* create */0], 0.0);
  var handler = Animated$BsReactNative.$$event(/* array */[{
          nativeEvent: {
            translationX: animatedValue
          }
        }], {
        useNativeDriver: true
      });
  var animatedProgress = AnimatedUtils$RerouteNative.interpolate(animatedValue, /* :: */[
        0.0,
        /* :: */[
          screenWidth,
          /* [] */0
        ]
      ], /* `float */[
        43435420,
        /* :: */[
          0.0,
          /* :: */[
            1.0,
            /* [] */0
          ]
        ]
      ], /* None */0, /* Some */[/* Clamp */1], /* None */0, /* None */0, /* () */0);
  var onStateChange = function ($$event, self) {
    var e = $$event.nativeEvent;
    var match = e.state;
    if (match !== 5) {
      return /* () */0;
    } else {
      var match$1 = e.translationX > (screenWidth / 2 | 0) || e.velocityX > 150.00;
      var toValue = match$1 ? screenWidth : 0;
      return Curry._3(Animated$BsReactNative.CompositeAnimation[/* start */1], Curry.app(Animated$BsReactNative.Value[/* Spring */20][/* animate */0], [
                      animatedValue,
                      /* `raw */[
                        5690856,
                        toValue
                      ],
                      /* None */0,
                      /* None */0,
                      /* None */0,
                      /* Some */[e.velocityX],
                      /* None */0,
                      /* None */0,
                      /* None */0,
                      /* None */0,
                      /* None */0,
                      /* None */0,
                      /* None */0,
                      /* None */0,
                      /* Some */[true],
                      /* None */0,
                      /* None */0,
                      /* () */0
                    ]), /* Some */[(function () {
                      if (toValue !== 0) {
                        var match = self[/* state */1];
                        var activeScreen = match[/* activeScreen */3];
                        var screens = match[/* screens */0];
                        Curry._2(Animated$BsReactNative.Value[/* setValue */1], Caml_array.caml_array_get(screens, activeScreen - 1 | 0)[/* animatedValue */3], 0.0);
                        Curry._2(Animated$BsReactNative.Value[/* setValue */1], Caml_array.caml_array_get(screens, activeScreen)[/* animatedValue */3], 1.0);
                        Curry._2(Animated$BsReactNative.Value[/* setValue */1], self[/* state */1][/* headerAnimatedValue */2], activeScreen - 1 | 0);
                        Curry._2(Animated$BsReactNative.Value[/* setValue */1], animatedValue, 0.0);
                        return Curry._1(self[/* send */3], /* RemoveLastScreen */0);
                      } else {
                        return 0;
                      }
                    })], /* () */0);
    }
  };
  var isActiveScreen = function (state, key) {
    return Caml_array.caml_array_get(state[/* screens */0], state[/* activeScreen */3])[/* key */1] === key;
  };
  var beginScreenAnimation = function (fromIdx, toIdx, self) {
    var match = fromIdx < toIdx;
    var action = match ? /* Push */893009402 : /* Pop */4003185;
    var match$1 = action === /* Push */893009402;
    var match$2 = match$1 ? /* tuple */[
        Caml_array.caml_array_get(self[/* state */1][/* screens */0], fromIdx),
        Caml_array.caml_array_get(self[/* state */1][/* screens */0], toIdx)
      ] : /* tuple */[
        Caml_array.caml_array_get(self[/* state */1][/* screens */0], toIdx),
        Caml_array.caml_array_get(self[/* state */1][/* screens */0], fromIdx)
      ];
    var second = match$2[1];
    var first = match$2[0];
    var match$3 = action >= 893009402 ? /* tuple */[
        /* tuple */[
          0.0,
          -1.0
        ],
        /* tuple */[
          1.0,
          0.0
        ]
      ] : /* tuple */[
        /* tuple */[
          -1.0,
          0.0
        ],
        /* tuple */[
          0.0,
          1.0
        ]
      ];
    var sndValues = match$3[1];
    var fstValues = match$3[0];
    Curry._2(Animated$BsReactNative.Value[/* setValue */1], first[/* animatedValue */3], fstValues[0]);
    Curry._2(Animated$BsReactNative.Value[/* setValue */1], second[/* animatedValue */3], sndValues[0]);
    Curry._3(Animated$BsReactNative.CompositeAnimation[/* start */1], Animated$BsReactNative.parallel(/* array */[
              Curry._2(second[/* animation */4][/* func */0], animatedValue, /* `raw */[
                    5690856,
                    0.0
                  ]),
              Curry._2(second[/* animation */4][/* func */0], self[/* state */1][/* headerAnimatedValue */2], /* `raw */[
                    5690856,
                    toIdx
                  ]),
              Curry._2(second[/* animation */4][/* func */0], first[/* animatedValue */3], /* `raw */[
                    5690856,
                    fstValues[1]
                  ]),
              Curry._2(second[/* animation */4][/* func */0], second[/* animatedValue */3], /* `raw */[
                    5690856,
                    sndValues[1]
                  ])
            ], {
              stopTogether: false
            }), /* Some */[(function (end_) {
              if (action === /* Pop */4003185 && end_.finished) {
                return Curry._1(self[/* send */3], /* RemoveStaleScreen */Block.__(2, [second[/* key */1]]));
              } else {
                return 0;
              }
            })], /* () */0);
    return /* () */0;
  };
  var component = ReasonReact.reducerComponent("StackNavigator");
  var make$1 = function (initialState, $staropt$star, $staropt$star$1, $staropt$star$2, children) {
    var onStateChange$1 = $staropt$star ? $staropt$star[0] : (function () {
          return /* () */0;
        });
    var headerComponent;
    if ($staropt$star$1) {
      headerComponent = $staropt$star$1[0];
    } else {
      var match = Platform$BsReactNative.os(/* () */0);
      headerComponent = match ? Header$RerouteNative.IOS[/* make */0] : Header$RerouteNative.Android[/* make */0];
    }
    var headerMode;
    if ($staropt$star$2) {
      headerMode = $staropt$star$2[0];
    } else {
      var match$1 = Platform$BsReactNative.os(/* () */0);
      headerMode = match$1 ? /* Floating */1 : /* Screen */0;
    }
    return /* record */[
            /* debugName */component[/* debugName */0],
            /* reactClassInternal */component[/* reactClassInternal */1],
            /* handedOffState */component[/* handedOffState */2],
            /* willReceiveProps */component[/* willReceiveProps */3],
            /* didMount */component[/* didMount */4],
            /* didUpdate */(function (param) {
                var self = param[/* newSelf */1];
                Curry._1(onStateChange$1, $$Array.map((function (screen) {
                            return screen[/* route */0];
                          }), self[/* state */1][/* screens */0]));
                if (Js_option.isSome(self[/* state */1][/* pendingTransition */1])) {
                  var match = Js_option.getExn(self[/* state */1][/* pendingTransition */1]);
                  var pendingToIdx = match[1];
                  if (Caml_array.caml_array_get(self[/* state */1][/* screens */0], pendingToIdx)[/* didMount */5]) {
                    Curry._1(self[/* send */3], /* DequeueTransition */1);
                    beginScreenAnimation(match[0], pendingToIdx, self);
                  }
                  
                }
                var fromIdx = param[/* oldSelf */0][/* state */1][/* activeScreen */3];
                var toIdx = self[/* state */1][/* activeScreen */3];
                var needsAnimation = self[/* state */1][/* screens */0].length > Math.max(toIdx, fromIdx);
                if (fromIdx !== toIdx && needsAnimation) {
                  if (Caml_array.caml_array_get(self[/* state */1][/* screens */0], toIdx)[/* didMount */5]) {
                    return beginScreenAnimation(fromIdx, toIdx, self);
                  } else {
                    return Curry._1(self[/* send */3], /* EnqueueTransition */Block.__(3, [
                                  fromIdx,
                                  toIdx
                                ]));
                  }
                } else {
                  return 0;
                }
              }),
            /* willUnmount */component[/* willUnmount */6],
            /* willUpdate */component[/* willUpdate */7],
            /* shouldUpdate */component[/* shouldUpdate */8],
            /* render */(function (self) {
                var size = self[/* state */1][/* screens */0].length;
                var screenWidth = Dimensions$BsReactNative.get(/* window */-762539024).width;
                var getAnimation = function (idx, screens) {
                  var match = (idx + 1 | 0) === size;
                  if (match) {
                    return Caml_array.caml_array_get(screens, idx)[/* animation */4];
                  } else {
                    return Caml_array.caml_array_get(screens, idx + 1 | 0)[/* animation */4];
                  }
                };
                var headerProps_000 = /* screens */$$Array.mapi((function (idx, screen) {
                        return /* record */[
                                /* header */screen[/* header */2],
                                /* animation */getAnimation(idx, self[/* state */1][/* screens */0]),
                                /* key */screen[/* key */1]
                              ];
                      }), self[/* state */1][/* screens */0]);
                var headerProps_001 = /* activeScreen */self[/* state */1][/* activeScreen */3];
                var headerProps_002 = /* animatedValue */Curry._2(Animated$BsReactNative.Value[/* add */16], self[/* state */1][/* headerAnimatedValue */2], Curry._2(Animated$BsReactNative.Value[/* multiply */18], animatedProgress, Curry._1(Animated$BsReactNative.Value[/* create */0], -1.0)));
                var headerProps_003 = function (key) {
                  return Curry._1(self[/* send */3], /* PopScreen */Block.__(4, [key]));
                };
                var headerProps = /* record */[
                  headerProps_000,
                  headerProps_001,
                  headerProps_002,
                  headerProps_003
                ];
                var match = headerMode === /* Floating */1;
                return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[stackContainer], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                                ReasonReact.element(/* None */0, /* None */0, make(handler, screenWidth, size > 1, Curry._1(self[/* handle */0], onStateChange), 20, {
                                          right: 20 - screenWidth | 0
                                        }, /* array */[ReasonReact.element(/* None */0, /* None */0, Curry.app(AnimatedComponents$BsReactNative.View[/* make */0], [
                                                    /* None */0,
                                                    /* None */0,
                                                    /* None */0,
                                                    /* None */0,
                                                    /* None */0,
                                                    /* None */0,
                                                    /* None */0,
                                                    /* None */0,
                                                    /* None */0,
                                                    /* Some */[flex],
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
                                                    /* array */[$$Array.mapi((function (idx, screen) {
                                                              var animation = size === 1 ? Style$BsReactNative.style(/* [] */0) : Curry._1(getAnimation(idx, self[/* state */1][/* screens */0])[/* forCard */1], Curry._2(Animated$BsReactNative.Value[/* add */16], animatedProgress, screen[/* animatedValue */3]));
                                                              var match = headerMode === /* Screen */0;
                                                              return ReasonReact.element(/* Some */[screen[/* key */1]], /* None */0, Curry.app(AnimatedComponents$BsReactNative.View[/* make */0], [
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
                                                                                      fill,
                                                                                      /* :: */[
                                                                                        screen[/* style */6],
                                                                                        /* :: */[
                                                                                          animation,
                                                                                          /* [] */0
                                                                                        ]
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
                                                                              /* array */[
                                                                                match ? ReasonReact.element(/* None */0, /* None */0, Curry._2(headerComponent, /* record */[
                                                                                            headerProps_000,
                                                                                            /* activeScreen */idx,
                                                                                            headerProps_002,
                                                                                            headerProps_003
                                                                                          ], /* array */[])) : ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[])),
                                                                                Curry._2(children, screen[/* route */0], /* record */[
                                                                                      /* push */(function (route) {
                                                                                          return Curry._1(self[/* send */3], /* PushScreen */Block.__(0, [
                                                                                                        route,
                                                                                                        screen[/* key */1]
                                                                                                      ]));
                                                                                        }),
                                                                                      /* setOptions */(function (opts) {
                                                                                          return Curry._1(self[/* send */3], /* SetOptions */Block.__(1, [
                                                                                                        opts,
                                                                                                        screen[/* key */1]
                                                                                                      ]));
                                                                                        }),
                                                                                      /* pop */(function () {
                                                                                          return Curry._1(self[/* send */3], /* PopScreen */Block.__(4, [screen[/* key */1]]));
                                                                                        })
                                                                                    ])
                                                                              ]
                                                                            ]));
                                                            }), self[/* state */1][/* screens */0])]
                                                  ]))])),
                                match ? ReasonReact.element(/* None */0, /* None */0, Curry._2(headerComponent, headerProps, /* array */[])) : ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[]))
                              ]));
              }),
            /* initialState */(function () {
                var activeScreen = initialState.length - 1 | 0;
                return /* record */[
                        /* screens */$$Array.mapi((function (idx, route) {
                                var match = idx === activeScreen;
                                return /* record */[
                                        /* route */route,
                                        /* key */Utils$RerouteNative.UUID[/* generate */1](/* () */0),
                                        /* header */Header$RerouteNative.$$default,
                                        /* animatedValue */Curry._1(Animated$BsReactNative.Value[/* create */0], match ? 0.0 : -1.0),
                                        /* animation */Animation$RerouteNative.$$default,
                                        /* didMount */false,
                                        /* style */card
                                      ];
                              }), initialState),
                        /* pendingTransition : None */0,
                        /* headerAnimatedValue */Curry._1(Animated$BsReactNative.Value[/* create */0], activeScreen),
                        /* activeScreen */activeScreen
                      ];
              }),
            /* retainedProps */component[/* retainedProps */11],
            /* reducer */(function (action, state) {
                if (typeof action === "number") {
                  if (action === 0) {
                    return /* Update */Block.__(0, [/* record */[
                                /* screens */Utils$RerouteNative.ReArray[/* remove */2](state[/* activeScreen */3], state[/* screens */0]),
                                /* pendingTransition : None */0,
                                /* headerAnimatedValue */state[/* headerAnimatedValue */2],
                                /* activeScreen */state[/* activeScreen */3] - 1 | 0
                              ]]);
                  } else {
                    return /* Update */Block.__(0, [/* record */[
                                /* screens */state[/* screens */0],
                                /* pendingTransition : None */0,
                                /* headerAnimatedValue */state[/* headerAnimatedValue */2],
                                /* activeScreen */state[/* activeScreen */3]
                              ]]);
                  }
                } else {
                  switch (action.tag | 0) {
                    case 0 : 
                        if (isActiveScreen(state, action[1])) {
                          var index = state[/* activeScreen */3] + 1 | 0;
                          return /* Update */Block.__(0, [/* record */[
                                      /* screens */Utils$RerouteNative.ReArray[/* append */1](/* record */[
                                            /* route */action[0],
                                            /* key */Utils$RerouteNative.UUID[/* generate */1](/* () */0),
                                            /* header */Header$RerouteNative.$$default,
                                            /* animatedValue */Curry._1(Animated$BsReactNative.Value[/* create */0], 1.0),
                                            /* animation */Animation$RerouteNative.$$default,
                                            /* didMount */false,
                                            /* style */card
                                          ], index, state[/* screens */0]),
                                      /* pendingTransition : None */0,
                                      /* headerAnimatedValue */state[/* headerAnimatedValue */2],
                                      /* activeScreen */index
                                    ]]);
                        } else {
                          return /* NoUpdate */0;
                        }
                    case 1 : 
                        var key = action[1];
                        var match = action[0];
                        var screens = state[/* screens */0].slice();
                        var idx = screens.findIndex((function (screen) {
                                return screen[/* key */1] === key;
                              }));
                        var init = Caml_array.caml_array_get(screens, idx);
                        Caml_array.caml_array_set(screens, idx, /* record */[
                              /* route */init[/* route */0],
                              /* key */init[/* key */1],
                              /* header */match[/* header */0],
                              /* animatedValue */init[/* animatedValue */3],
                              /* animation */Js_option.getWithDefault(Caml_array.caml_array_get(screens, idx)[/* animation */4], match[/* animation */1]),
                              /* didMount */true,
                              /* style */Js_option.getWithDefault(Caml_array.caml_array_get(screens, idx)[/* style */6], match[/* style */2])
                            ]);
                        return /* Update */Block.__(0, [/* record */[
                                    /* screens */screens,
                                    /* pendingTransition */state[/* pendingTransition */1],
                                    /* headerAnimatedValue */state[/* headerAnimatedValue */2],
                                    /* activeScreen */state[/* activeScreen */3]
                                  ]]);
                    case 2 : 
                        var key$1 = action[0];
                        var idx$1 = state[/* screens */0].findIndex((function (screen) {
                                return screen[/* key */1] === key$1;
                              }));
                        return /* Update */Block.__(0, [/* record */[
                                    /* screens */Utils$RerouteNative.ReArray[/* remove */2](idx$1, state[/* screens */0]),
                                    /* pendingTransition */state[/* pendingTransition */1],
                                    /* headerAnimatedValue */state[/* headerAnimatedValue */2],
                                    /* activeScreen */state[/* activeScreen */3]
                                  ]]);
                    case 3 : 
                        return /* Update */Block.__(0, [/* record */[
                                    /* screens */state[/* screens */0],
                                    /* pendingTransition : Some */[/* tuple */[
                                        action[0],
                                        action[1]
                                      ]],
                                    /* headerAnimatedValue */state[/* headerAnimatedValue */2],
                                    /* activeScreen */state[/* activeScreen */3]
                                  ]]);
                    case 4 : 
                        if (state[/* activeScreen */3] > 0 && isActiveScreen(state, action[0])) {
                          return /* Update */Block.__(0, [/* record */[
                                      /* screens */state[/* screens */0],
                                      /* pendingTransition : None */0,
                                      /* headerAnimatedValue */state[/* headerAnimatedValue */2],
                                      /* activeScreen */state[/* activeScreen */3] - 1 | 0
                                    ]]);
                        } else {
                          return /* NoUpdate */0;
                        }
                    
                  }
                }
              }),
            /* subscriptions */component[/* subscriptions */13],
            /* jsElementWrapped */component[/* jsElementWrapped */14]
          ];
  };
  var component$1 = ReasonReact.statelessComponent("CallstackScreen");
  var make$2 = function (navigation, style, headerTitle, headerStyle, headerLeft, headerCenter, headerRight, animation, children) {
    return /* record */[
            /* debugName */component$1[/* debugName */0],
            /* reactClassInternal */component$1[/* reactClassInternal */1],
            /* handedOffState */component$1[/* handedOffState */2],
            /* willReceiveProps */component$1[/* willReceiveProps */3],
            /* didMount */(function () {
                Curry._1(navigation[/* setOptions */1], /* record */[
                      /* header : record */[
                        /* style */headerStyle,
                        /* title */headerTitle,
                        /* center */headerCenter,
                        /* left */headerLeft,
                        /* right */headerRight
                      ],
                      /* animation */animation,
                      /* style */style
                    ]);
                return /* () */0;
              }),
            /* didUpdate */component$1[/* didUpdate */5],
            /* willUnmount */component$1[/* willUnmount */6],
            /* willUpdate */component$1[/* willUpdate */7],
            /* shouldUpdate */component$1[/* shouldUpdate */8],
            /* render */(function () {
                var body = Curry._1(children, /* () */0);
                return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[Style$BsReactNative.style(/* :: */[
                                        Style$BsReactNative.flex(1.0),
                                        /* [] */0
                                      ])], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[body]));
              }),
            /* initialState */component$1[/* initialState */10],
            /* retainedProps */component$1[/* retainedProps */11],
            /* reducer */component$1[/* reducer */12],
            /* subscriptions */component$1[/* subscriptions */13],
            /* jsElementWrapped */component$1[/* jsElementWrapped */14]
          ];
  };
  return [[
            include[0],
            make$1,
            0,
            [/* make */make$2]
          ]];
}

exports.CreateStackNavigator = CreateStackNavigator;
/* fill Not a pure module */
