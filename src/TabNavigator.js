'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var $$String = require("bs-platform/lib/js/string.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Text$BsReactNative = require("bs-react-native/src/components/text.js");
var View$BsReactNative = require("bs-react-native/src/components/view.js");
var Image$BsReactNative = require("bs-react-native/src/components/image.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");
var Platform$BsReactNative = require("bs-react-native/src/platform.js");
var Dimensions$BsReactNative = require("bs-react-native/src/dimensions.js");
var StyleSheet$BsReactNative = require("bs-react-native/src/styleSheet.js");
var SafeAreaView$BsReactNative = require("bs-react-native/src/components/safeAreaView.js");
var TouchableWithoutFeedback$BsReactNative = require("bs-react-native/src/components/touchableWithoutFeedback.js");

var tabContainer = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1),
      /* [] */0
    ]);

function screenContainer(isActive) {
  if (isActive) {
    return Style$BsReactNative.style(/* :: */[
                Style$BsReactNative.position(/* Absolute */0),
                /* :: */[
                  Style$BsReactNative.top(/* Pt */Block.__(0, [0])),
                  /* :: */[
                    Style$BsReactNative.right(/* Pt */Block.__(0, [0])),
                    /* :: */[
                      Style$BsReactNative.bottom(/* Pt */Block.__(0, [0])),
                      /* :: */[
                        Style$BsReactNative.left(/* Pt */Block.__(0, [0])),
                        /* [] */0
                      ]
                    ]
                  ]
                ]
              ]);
  } else {
    return Style$BsReactNative.style(/* :: */[
                Style$BsReactNative.position(/* Absolute */0),
                /* :: */[
                  Style$BsReactNative.top(/* Pt */Block.__(0, [0])),
                  /* :: */[
                    Style$BsReactNative.right(/* Pt */Block.__(0, [0])),
                    /* :: */[
                      Style$BsReactNative.bottom(/* Pt */Block.__(0, [0])),
                      /* :: */[
                        Style$BsReactNative.left(/* Pt */Block.__(0, [0])),
                        /* :: */[
                          Style$BsReactNative.opacity(/* Float */Block.__(0, [0])),
                          /* [] */0
                        ]
                      ]
                    ]
                  ]
                ]
              ]);
  }
}

function tabBarContainer(safeAreaViewBackgroundColor, renderTabBar) {
  return Style$BsReactNative.style(/* :: */[
              Style$BsReactNative.flex(1),
              /* :: */[
                Style$BsReactNative.backgroundColor(safeAreaViewBackgroundColor ? /* String */Block.__(0, [safeAreaViewBackgroundColor[0]]) : (
                        renderTabBar ? /* String */Block.__(0, ["transparent"]) : /* String */Block.__(0, ["#f7f7f7"])
                      )),
                /* [] */0
              ]
            ]);
}

var match = Platform$BsReactNative.os(/* () */0);

var tabBar = match ? Style$BsReactNative.style(/* :: */[
        Style$BsReactNative.flexDirection(/* Row */0),
        /* :: */[
          Style$BsReactNative.backgroundColor(/* String */Block.__(0, ["#f7f7f7"])),
          /* :: */[
            Style$BsReactNative.height(/* Pt */Block.__(0, [49])),
            /* :: */[
              Style$BsReactNative.position(/* Absolute */0),
              /* :: */[
                Style$BsReactNative.left(/* Pt */Block.__(0, [0.0])),
                /* :: */[
                  Style$BsReactNative.right(/* Pt */Block.__(0, [0.0])),
                  /* :: */[
                    Style$BsReactNative.bottom(/* Pt */Block.__(0, [0.0])),
                    /* :: */[
                      Style$BsReactNative.borderTopWidth(StyleSheet$BsReactNative.hairlineWidth),
                      /* :: */[
                        Style$BsReactNative.borderTopColor(/* String */Block.__(0, ["rgba(0, 0, 0, 0.3)"])),
                        /* [] */0
                      ]
                    ]
                  ]
                ]
              ]
            ]
          ]
        ]
      ]) : Style$BsReactNative.style(/* :: */[
        Style$BsReactNative.flexDirection(/* Row */0),
        /* :: */[
          Style$BsReactNative.backgroundColor(/* String */Block.__(0, ["#fff"])),
          /* :: */[
            Style$BsReactNative.height(/* Pt */Block.__(0, [48])),
            /* :: */[
              Style$BsReactNative.position(/* Absolute */0),
              /* :: */[
                Style$BsReactNative.left(/* Pt */Block.__(0, [0.0])),
                /* :: */[
                  Style$BsReactNative.right(/* Pt */Block.__(0, [0.0])),
                  /* :: */[
                    Style$BsReactNative.top(/* Pt */Block.__(0, [0.0])),
                    /* :: */[
                      Style$BsReactNative.elevation(4),
                      /* :: */[
                        Style$BsReactNative.shadowOpacity(0.1),
                        /* :: */[
                          Style$BsReactNative.zIndex(0),
                          /* [] */0
                        ]
                      ]
                    ]
                  ]
                ]
              ]
            ]
          ]
        ]
      ]);

function tabBarIndicator(denominator, itemIndex, indicatorColor) {
  var itemWidth = Dimensions$BsReactNative.get(/* window */-762539024).width / denominator;
  return Style$BsReactNative.style(/* :: */[
              Style$BsReactNative.position(/* Absolute */0),
              /* :: */[
                Style$BsReactNative.bottom(/* Pt */Block.__(0, [0])),
                /* :: */[
                  Style$BsReactNative.height(/* Pt */Block.__(0, [2])),
                  /* :: */[
                    Style$BsReactNative.left(/* Pt */Block.__(0, [itemWidth * itemIndex])),
                    /* :: */[
                      Style$BsReactNative.backgroundColor(/* String */Block.__(0, [indicatorColor ? indicatorColor[0] : "blue"])),
                      /* :: */[
                        Style$BsReactNative.width(/* Pt */Block.__(0, [itemWidth])),
                        /* [] */0
                      ]
                    ]
                  ]
                ]
              ]
            ]);
}

var match$1 = Platform$BsReactNative.os(/* () */0);

var tabBarItemContainer = match$1 ? Style$BsReactNative.style(/* :: */[
        Style$BsReactNative.flex(1),
        /* :: */[
          Style$BsReactNative.justifyContent(/* Center */2),
          /* :: */[
            Style$BsReactNative.alignItems(/* Center */2),
            /* [] */0
          ]
        ]
      ]) : Style$BsReactNative.style(/* :: */[
        Style$BsReactNative.flex(1),
        /* :: */[
          Style$BsReactNative.justifyContent(/* Center */2),
          /* :: */[
            Style$BsReactNative.alignItems(/* Center */2),
            /* [] */0
          ]
        ]
      ]);

var tabBarItem = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.alignItems(/* Center */2),
      /* [] */0
    ]);

var match$2 = Platform$BsReactNative.os(/* () */0);

var tabBarItemIcon = match$2 ? Style$BsReactNative.style(/* :: */[
        Style$BsReactNative.height(/* Pt */Block.__(0, [20])),
        /* :: */[
          Style$BsReactNative.width(/* Pt */Block.__(0, [20])),
          /* [] */0
        ]
      ]) : Style$BsReactNative.style(/* :: */[
        Style$BsReactNative.height(/* Pt */Block.__(0, [24])),
        /* :: */[
          Style$BsReactNative.width(/* Pt */Block.__(0, [24])),
          /* :: */[
            Style$BsReactNative.padding(/* Pt */Block.__(0, [0.0])),
            /* :: */[
              Style$BsReactNative.margin(/* Pt */Block.__(0, [0.0])),
              /* [] */0
            ]
          ]
        ]
      ]);

function tabBarItemText(textSize) {
  var match = Platform$BsReactNative.os(/* () */0);
  if (match) {
    return Style$BsReactNative.style(/* :: */[
                Style$BsReactNative.bottom(/* Pt */Block.__(0, [textSize ? 0 : -6])),
                /* :: */[
                  Style$BsReactNative.color(/* String */Block.__(0, ["#2180f7"])),
                  /* :: */[
                    Style$BsReactNative.fontSize(/* Float */Block.__(0, [textSize ? 13.0 : 10.0])),
                    /* [] */0
                  ]
                ]
              ]);
  } else {
    return Style$BsReactNative.style(/* :: */[
                Style$BsReactNative.paddingTop(textSize ? /* Pt */Block.__(0, [0]) : /* Pt */Block.__(0, [10])),
                /* :: */[
                  Style$BsReactNative.bottom(textSize ? /* Pt */Block.__(0, [0]) : /* Pt */Block.__(0, [4])),
                  /* :: */[
                    Style$BsReactNative.margin(/* Pt */Block.__(0, [0])),
                    /* :: */[
                      Style$BsReactNative.color(/* String */Block.__(0, ["#2180f7"])),
                      /* :: */[
                        Style$BsReactNative.fontSize(/* Float */Block.__(0, [14.0])),
                        /* [] */0
                      ]
                    ]
                  ]
                ]
              ]);
  }
}

function CreateTabNavigator() {
  var component = ReasonReact.statelessComponent("TabBarItem");
  var make = function (label, icon, style, _) {
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
                if (icon) {
                  var tmp;
                  if (label === "") {
                    tmp = null;
                  } else {
                    var match = Platform$BsReactNative.os(/* () */0);
                    var itemText = match ? label : $$String.uppercase(label);
                    tmp = ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[Style$BsReactNative.concat(/* :: */[
                                    tabBarItemText(/* Small */0),
                                    /* :: */[
                                      style ? style[0] : Style$BsReactNative.style(/* [] */0),
                                      /* [] */0
                                    ]
                                  ])], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[itemText]));
                  }
                  return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[tabBarItem], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                                  ReasonReact.element(/* None */0, /* None */0, Image$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[icon[0]], /* Some */[tabBarItemIcon], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[])),
                                  tmp
                                ]));
                } else if (label === "") {
                  return null;
                } else {
                  var match$1 = Platform$BsReactNative.os(/* () */0);
                  var itemText$1 = match$1 ? label : $$String.uppercase(label);
                  return ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[Style$BsReactNative.concat(/* :: */[
                                        tabBarItemText(/* Regular */1),
                                        /* :: */[
                                          style ? style[0] : Style$BsReactNative.style(/* [] */0),
                                          /* [] */0
                                        ]
                                      ])], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[itemText$1]));
                }
              }),
            /* initialState */component[/* initialState */10],
            /* retainedProps */component[/* retainedProps */11],
            /* reducer */component[/* reducer */12],
            /* subscriptions */component[/* subscriptions */13],
            /* jsElementWrapped */component[/* jsElementWrapped */14]
          ];
  };
  var Item = /* module */[
    /* component */component,
    /* make */make
  ];
  var component$1 = ReasonReact.statelessComponent("TabBar");
  var make$1 = function (tabBarProps, _) {
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
            /* render */(function () {
                var match = Platform$BsReactNative.os(/* () */0);
                return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[tabBar], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                                match ? null : $$Array.mapi((function (index, screen) {
                                          var isActive = tabBarProps[/* currentRoute */1] === screen[/* route */0];
                                          if (isActive) {
                                            return ReasonReact.element(/* Some */[String(index)], /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[tabBarIndicator(tabBarProps[/* screens */0].length, index, tabBarProps[/* indicatorColor */3])], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[]));
                                          } else {
                                            return null;
                                          }
                                        }), tabBarProps[/* screens */0]),
                                $$Array.mapi((function (index, screen) {
                                        var isActive = tabBarProps[/* currentRoute */1] === screen[/* route */0];
                                        return ReasonReact.element(/* Some */[String(index)], /* None */0, TouchableWithoutFeedback$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[(function () {
                                                              return Curry._1(tabBarProps[/* jumpTo */2], screen[/* route */0]);
                                                            })], /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[tabBarItemContainer], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[Curry._1(screen[/* tabItem */1], /* record */[/* isActive */isActive])]))]));
                                      }), tabBarProps[/* screens */0])
                              ]));
              }),
            /* initialState */component$1[/* initialState */10],
            /* retainedProps */component$1[/* retainedProps */11],
            /* reducer */component$1[/* reducer */12],
            /* subscriptions */component$1[/* subscriptions */13],
            /* jsElementWrapped */component$1[/* jsElementWrapped */14]
          ];
  };
  var component$2 = ReasonReact.reducerComponent("TabNavigator");
  var make$2 = function (initialRoute, routes, renderTabBar, safeAreaViewBackgroundColor, indicatorColor, children) {
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
            /* render */(function (self) {
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
                                /* Some */[tabBarContainer(safeAreaViewBackgroundColor, renderTabBar)],
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
                                /* array */[ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[tabContainer], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                                            $$Array.mapi((function (index, screen) {
                                                    var isActive = self[/* state */1][/* currentRoute */1] === screen[/* route */0];
                                                    return ReasonReact.element(/* Some */[String(index)], /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[isActive ? /* auto */-1065951377 : /* none */-922086728], /* None */0, /* Some */[screenContainer(isActive)], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[Curry._1(children, /* record */[
                                                                          /* screens */self[/* state */1][/* screens */0],
                                                                          /* currentRoute */screen[/* route */0],
                                                                          /* jumpTo */(function (route) {
                                                                              return Curry._1(self[/* send */3], /* JumpTo */Block.__(0, [route]));
                                                                            }),
                                                                          /* setOptions */(function (options) {
                                                                              return Curry._1(self[/* send */3], /* SetOptions */Block.__(1, [
                                                                                            options,
                                                                                            index
                                                                                          ]));
                                                                            }),
                                                                          /* isActive */isActive
                                                                        ])]));
                                                  }), self[/* state */1][/* screens */0]),
                                            renderTabBar ? Curry._1(renderTabBar[0], /* record */[
                                                    /* screens */self[/* state */1][/* screens */0],
                                                    /* currentRoute */self[/* state */1][/* currentRoute */1],
                                                    /* jumpTo */(function (route) {
                                                        return Curry._1(self[/* send */3], /* JumpTo */Block.__(0, [route]));
                                                      }),
                                                    /* indicatorColor */indicatorColor
                                                  ]) : ReasonReact.element(/* None */0, /* None */0, make$1(/* record */[
                                                        /* screens */self[/* state */1][/* screens */0],
                                                        /* currentRoute */self[/* state */1][/* currentRoute */1],
                                                        /* jumpTo */(function (route) {
                                                            return Curry._1(self[/* send */3], /* JumpTo */Block.__(0, [route]));
                                                          }),
                                                        /* indicatorColor */indicatorColor
                                                      ], /* array */[]))
                                          ]))]
                              ]));
              }),
            /* initialState */(function () {
                return /* record */[
                        /* screens */$$Array.map((function (route) {
                                return /* record */[
                                        /* route */route,
                                        /* tabItem */(function () {
                                            return null;
                                          })
                                      ];
                              }), routes),
                        /* currentRoute */initialRoute
                      ];
              }),
            /* retainedProps */component$2[/* retainedProps */11],
            /* reducer */(function (action, state) {
                if (action.tag) {
                  var index = action[1];
                  var screens = state[/* screens */0].slice();
                  var init = Caml_array.caml_array_get(screens, index);
                  Caml_array.caml_array_set(screens, index, /* record */[
                        /* route */init[/* route */0],
                        /* tabItem */action[0][/* tabItem */0]
                      ]);
                  return /* Update */Block.__(0, [/* record */[
                              /* screens */screens,
                              /* currentRoute */state[/* currentRoute */1]
                            ]]);
                } else {
                  var route = action[0];
                  if (route !== state[/* currentRoute */1]) {
                    return /* Update */Block.__(0, [/* record */[
                                /* screens */state[/* screens */0],
                                /* currentRoute */route
                              ]]);
                  } else {
                    return /* NoUpdate */0;
                  }
                }
              }),
            /* subscriptions */component$2[/* subscriptions */13],
            /* jsElementWrapped */component$2[/* jsElementWrapped */14]
          ];
  };
  var component$3 = ReasonReact.statelessComponent("Screen");
  var make$3 = function (navigation, tabItem, children) {
    return /* record */[
            /* debugName */component$3[/* debugName */0],
            /* reactClassInternal */component$3[/* reactClassInternal */1],
            /* handedOffState */component$3[/* handedOffState */2],
            /* willReceiveProps */component$3[/* willReceiveProps */3],
            /* didMount */(function () {
                Curry._1(navigation[/* setOptions */3], /* record */[/* tabItem */tabItem]);
                return /* () */0;
              }),
            /* didUpdate */component$3[/* didUpdate */5],
            /* willUnmount */component$3[/* willUnmount */6],
            /* willUpdate */component$3[/* willUpdate */7],
            /* shouldUpdate */component$3[/* shouldUpdate */8],
            /* render */(function () {
                var match = navigation[/* isActive */4];
                if (match) {
                  return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[tabContainer], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[Curry._1(children, /* () */0)]));
                } else {
                  return null;
                }
              }),
            /* initialState */component$3[/* initialState */10],
            /* retainedProps */component$3[/* retainedProps */11],
            /* reducer */component$3[/* reducer */12],
            /* subscriptions */component$3[/* subscriptions */13],
            /* jsElementWrapped */component$3[/* jsElementWrapped */14]
          ];
  };
  return [[
            make$2,
            [/* make */make$3],
            [
              [/* Item */Item[1]],
              /* make */make$1
            ]
          ]];
}

exports.CreateTabNavigator = CreateTabNavigator;
/* tabContainer Not a pure module */
