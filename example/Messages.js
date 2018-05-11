'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Text$BsReactNative = require("bs-react-native/src/components/text.js");
var View$BsReactNative = require("bs-react-native/src/components/view.js");
var Image$BsReactNative = require("bs-react-native/src/components/image.js");
var Style$BsReactNative = require("bs-react-native/src/style.js");
var FlatList$BsReactNative = require("bs-react-native/src/components/flatList.js");
var Dimensions$BsReactNative = require("bs-react-native/src/dimensions.js");
var NavigationConfig$RerouteNative = require("./NavigationConfig.js");
var TouchableOpacity$BsReactNative = require("bs-react-native/src/components/touchableOpacity.js");

var component = ReasonReact.statelessComponent("Messages");

var itemWidth = Dimensions$BsReactNative.get(/* screen */-950191252).width;

function container(custom) {
  return Style$BsReactNative.style(/* :: */[
              Style$BsReactNative.flex(1),
              /* :: */[
                Style$BsReactNative.alignItems(/* Center */2),
                /* :: */[
                  Style$BsReactNative.justifyContent(/* Center */2),
                  /* :: */[
                    Style$BsReactNative.marginTop(/* Pt */Block.__(0, [custom ? 80 : 0])),
                    /* [] */0
                  ]
                ]
              ]
            ]);
}

var title = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.color(/* String */Block.__(0, ["#000"])),
      /* :: */[
        Style$BsReactNative.fontSize(/* Float */Block.__(0, [24])),
        /* [] */0
      ]
    ]);

var listItem = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flex(1),
      /* :: */[
        Style$BsReactNative.flexDirection(/* Row */0),
        /* :: */[
          Style$BsReactNative.width(/* Pt */Block.__(0, [itemWidth])),
          /* :: */[
            Style$BsReactNative.height(/* Pt */Block.__(0, [35])),
            /* :: */[
              Style$BsReactNative.justifyContent(/* SpaceBetween */5),
              /* :: */[
                Style$BsReactNative.alignItems(/* Center */2),
                /* :: */[
                  Style$BsReactNative.paddingHorizontal(/* Pt */Block.__(0, [5])),
                  /* :: */[
                    Style$BsReactNative.borderColor(/* String */Block.__(0, ["gray"])),
                    /* :: */[
                      Style$BsReactNative.borderBottomWidth(0.2),
                      /* :: */[
                        Style$BsReactNative.backgroundColor(/* String */Block.__(0, ["white"])),
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

var name = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.color(/* String */Block.__(0, ["#323232"])),
      /* :: */[
        Style$BsReactNative.fontSize(/* Float */Block.__(0, [15])),
        /* [] */0
      ]
    ]);

var rightActions = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.flexDirection(/* Row */0),
      /* :: */[
        Style$BsReactNative.justifyContent(/* SpaceBetween */5),
        /* :: */[
          Style$BsReactNative.alignItems(/* Center */2),
          /* [] */0
        ]
      ]
    ]);

var icon = Style$BsReactNative.style(/* :: */[
      Style$BsReactNative.height(/* Pt */Block.__(0, [20])),
      /* :: */[
        Style$BsReactNative.width(/* Pt */Block.__(0, [20])),
        /* [] */0
      ]
    ]);

var Styles = /* module */[
  /* container */container,
  /* title */title,
  /* listItem */listItem,
  /* name */name,
  /* rightActions */rightActions,
  /* icon */icon
];

var data = /* array */[
  /* record */[
    /* name */"Davin Roth",
    /* count */645
  ],
  /* record */[
    /* name */"Milton Walsh",
    /* count */12
  ],
  /* record */[
    /* name */"Malakai Brady",
    /* count */99
  ],
  /* record */[
    /* name */"Xavier Obrien",
    /* count */1
  ],
  /* record */[
    /* name */"Ariel Gill",
    /* count */32
  ],
  /* record */[
    /* name */"Avery Lozano",
    /* count */15
  ],
  /* record */[
    /* name */"Davian Osborne",
    /* count */7
  ],
  /* record */[
    /* name */"Jovan Vega",
    /* count */2
  ]
];

function renderItem(param) {
  return FlatList$BsReactNative.renderItem((function (contact) {
                return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[listItem], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                                ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[name], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[contact[/* item */0][/* name */0]])),
                                ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[rightActions], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                                          ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[String(contact[/* item */0][/* count */1])])),
                                          ReasonReact.element(/* None */0, /* None */0, TouchableOpacity$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, Image$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[/* Required */Block.__(1, [require("./assets/right.png")])], /* Some */[icon], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[]))]))
                                        ]))
                              ]));
              }), param);
}

function extractor(item, _) {
  return item[/* name */0];
}

function make(navigation, custom, _) {
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
                                return ReasonReact.element(/* None */0, /* None */0, Curry._4(NavigationConfig$RerouteNative.TabNavigator[/* TabBar */2][/* Item */0][/* make */0], "Messages", /* None */0, /* Some */[Style$BsReactNative.style(/* :: */[
                                                      Style$BsReactNative.color(/* String */Block.__(0, [param[/* isActive */0] ? "blue" : "gray"])),
                                                      /* [] */0
                                                    ])], /* array */[]));
                              }), (function () {
                                return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container(custom)], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, FlatList$BsReactNative.make(data, renderItem, extractor, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[]))]));
                              })));
            }),
          /* initialState */component[/* initialState */10],
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */component[/* reducer */12],
          /* subscriptions */component[/* subscriptions */13],
          /* jsElementWrapped */component[/* jsElementWrapped */14]
        ];
}

exports.component = component;
exports.itemWidth = itemWidth;
exports.Styles = Styles;
exports.data = data;
exports.renderItem = renderItem;
exports.extractor = extractor;
exports.make = make;
/* component Not a pure module */
