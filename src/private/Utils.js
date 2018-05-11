'use strict';

var $$Map = require("bs-platform/lib/js/map.js");
var Curry = require("bs-platform/lib/js/curry.js");
var Caml_obj = require("bs-platform/lib/js/caml_obj.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");

var count = [0];

function generate() {
  count[0] = count[0] + 1 | 0;
  return "id-" + (new Date(Date.now()).toString() + String(count[0]));
}

var UUID = /* module */[
  /* count */count,
  /* generate */generate
];

function set(el, idx, arr) {
  var copied = arr.slice();
  Caml_array.caml_array_set(copied, idx, el);
  return copied;
}

function append(el, idx, arr) {
  var copied = arr.slice();
  copied.splice(idx, 0, el);
  return copied;
}

function remove(idx, arr) {
  var copied = arr.slice();
  copied.splice(idx, idx);
  return copied;
}

var ReArray = /* module */[
  /* set */set,
  /* append */append,
  /* remove */remove
];

function option_map(fn, opt_value) {
  if (opt_value) {
    return /* Some */[Curry._1(fn, opt_value[0])];
  } else {
    return /* None */0;
  }
}

var compare = Caml_obj.caml_compare;

var include = $$Map.Make(/* module */[/* compare */compare]);

var exists = include[12];

function hasKey(skey, map) {
  return Curry._2(exists, (function (key, _) {
                return key === skey;
              }), map);
}

var StringMap_000 = /* empty */include[0];

var StringMap_001 = /* is_empty */include[1];

var StringMap_002 = /* mem */include[2];

var StringMap_003 = /* add */include[3];

var StringMap_004 = /* singleton */include[4];

var StringMap_005 = /* remove */include[5];

var StringMap_006 = /* merge */include[6];

var StringMap_007 = /* compare */include[7];

var StringMap_008 = /* equal */include[8];

var StringMap_009 = /* iter */include[9];

var StringMap_010 = /* fold */include[10];

var StringMap_011 = /* for_all */include[11];

var StringMap_013 = /* filter */include[13];

var StringMap_014 = /* partition */include[14];

var StringMap_015 = /* cardinal */include[15];

var StringMap_016 = /* bindings */include[16];

var StringMap_017 = /* min_binding */include[17];

var StringMap_018 = /* max_binding */include[18];

var StringMap_019 = /* choose */include[19];

var StringMap_020 = /* split */include[20];

var StringMap_021 = /* find */include[21];

var StringMap_022 = /* map */include[22];

var StringMap_023 = /* mapi */include[23];

var StringMap = /* module */[
  StringMap_000,
  StringMap_001,
  StringMap_002,
  StringMap_003,
  StringMap_004,
  StringMap_005,
  StringMap_006,
  StringMap_007,
  StringMap_008,
  StringMap_009,
  StringMap_010,
  StringMap_011,
  /* exists */exists,
  StringMap_013,
  StringMap_014,
  StringMap_015,
  StringMap_016,
  StringMap_017,
  StringMap_018,
  StringMap_019,
  StringMap_020,
  StringMap_021,
  StringMap_022,
  StringMap_023,
  /* hasKey */hasKey
];

exports.UUID = UUID;
exports.ReArray = ReArray;
exports.option_map = option_map;
exports.StringMap = StringMap;
/* include Not a pure module */
