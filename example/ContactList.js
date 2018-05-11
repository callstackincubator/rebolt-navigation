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

var component = ReasonReact.statelessComponent("Contacts");

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

function online(online$1) {
  return Style$BsReactNative.style(/* :: */[
              Style$BsReactNative.height(/* Pt */Block.__(0, [10])),
              /* :: */[
                Style$BsReactNative.width(/* Pt */Block.__(0, [10])),
                /* :: */[
                  Style$BsReactNative.backgroundColor(/* String */Block.__(0, [online$1 ? "#4cd964" : "#ff3b3a"])),
                  /* :: */[
                    Style$BsReactNative.borderRadius(20),
                    /* :: */[
                      Style$BsReactNative.marginHorizontal(/* Pt */Block.__(0, [7])),
                      /* [] */0
                    ]
                  ]
                ]
              ]
            ]);
}

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
  /* online */online,
  /* rightActions */rightActions,
  /* icon */icon
];

var data = /* array */[
  /* record */[
    /* name */"John Doe",
    /* online */true
  ],
  /* record */[
    /* name */"Marry Jane",
    /* online */false
  ],
  /* record */[
    /* name */"Mario Speedwagon",
    /* online */true
  ],
  /* record */[
    /* name */"Petey Cruiser",
    /* online */false
  ],
  /* record */[
    /* name */"Anna Sthesia",
    /* online */true
  ],
  /* record */[
    /* name */"Paul Molive",
    /* online */true
  ],
  /* record */[
    /* name */"Anna Mull",
    /* online */false
  ],
  /* record */[
    /* name */"Gail Forcewind",
    /* online */false
  ],
  /* record */[
    /* name */"Paige Turner",
    /* online */false
  ],
  /* record */[
    /* name */"Bob Frapples",
    /* online */false
  ],
  /* record */[
    /* name */"Walter Melon",
    /* online */true
  ],
  /* record */[
    /* name */"Nick R. Bocker",
    /* online */true
  ],
  /* record */[
    /* name */"Barb Ackue",
    /* online */true
  ],
  /* record */[
    /* name */"Buck Kinnear",
    /* online */true
  ],
  /* record */[
    /* name */"Greta Life",
    /* online */false
  ],
  /* record */[
    /* name */"Ira Membrit",
    /* online */false
  ],
  /* record */[
    /* name */"Shonda Leer",
    /* online */false
  ],
  /* record */[
    /* name */"Brock Lee",
    /* online */false
  ],
  /* record */[
    /* name */"Maya Didas",
    /* online */false
  ],
  /* record */[
    /* name */"Rick O'Shea",
    /* online */false
  ],
  /* record */[
    /* name */"Pete Sariya",
    /* online */false
  ],
  /* record */[
    /* name */"Monty Carlo",
    /* online */false
  ]
];

function renderItem(nav) {
  return (function (param) {
      return FlatList$BsReactNative.renderItem((function (contact) {
                    return ReasonReact.element(/* None */0, /* None */0, TouchableOpacity$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[listItem], /* None */0, /* Some */[(function () {
                                          return Curry._1(nav[/* push */0], /* UserProfile */5);
                                        })], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                                    ReasonReact.element(/* None */0, /* None */0, Text$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[name], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* array */[contact[/* item */0][/* name */0]])),
                                    ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[rightActions], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[
                                              ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[online(contact[/* item */0][/* online */1])], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[])),
                                              ReasonReact.element(/* None */0, /* None */0, TouchableOpacity$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, Image$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[/* Required */Block.__(1, [require("./assets/right.png")])], /* Some */[icon], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[]))]))
                                            ]))
                                  ]));
                  }), param);
    });
}

function extractor(item, _) {
  return item[/* name */0];
}

function make(navigation, stackNavigation, custom, _) {
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
                                return ReasonReact.element(/* None */0, /* None */0, Curry._4(NavigationConfig$RerouteNative.TabNavigator[/* TabBar */2][/* Item */0][/* make */0], "Contacts", /* None */0, /* Some */[Style$BsReactNative.style(/* :: */[
                                                      Style$BsReactNative.color(/* String */Block.__(0, [param[/* isActive */0] ? "blue" : "gray"])),
                                                      /* [] */0
                                                    ])], /* array */[]));
                              }), (function () {
                                return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[container(custom)], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, FlatList$BsReactNative.make(data, renderItem(stackNavigation), extractor, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[]))]));
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
