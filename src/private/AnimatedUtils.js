'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Utils$RerouteNative = require("./Utils.js");

function extrapolateString(x) {
  switch (x) {
    case 0 : 
        return "extend";
    case 1 : 
        return "clamp";
    case 2 : 
        return "identity";
    
  }
}

function interpolate(value, inputRange, outputRange, easing, extrapolate, extrapolateLeft, extrapolateRight, _) {
  var tmp = {
    inputRange: $$Array.of_list(inputRange),
    outputRange: $$Array.of_list(outputRange[1])
  };
  if (easing) {
    tmp.easing = easing[0];
  }
  var tmp$1 = Utils$RerouteNative.option_map(extrapolateString, extrapolate);
  if (tmp$1) {
    tmp.extrapolate = tmp$1[0];
  }
  var tmp$2 = Utils$RerouteNative.option_map(extrapolateString, extrapolateLeft);
  if (tmp$2) {
    tmp.extrapolateLeft = tmp$2[0];
  }
  var tmp$3 = Utils$RerouteNative.option_map(extrapolateString, extrapolateRight);
  if (tmp$3) {
    tmp.extrapolateRight = tmp$3[0];
  }
  return value.interpolate(tmp);
}

exports.extrapolateString = extrapolateString;
exports.interpolate = interpolate;
/* Utils-RerouteNative Not a pure module */
