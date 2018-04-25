module CreatePersistor = (Config: {type route;}) => {
  module Persistor = {
    let encode: array(Config.route) => Js.Json.t = [%bs.raw
      {|
      (function(obj) {
        var data = JSON.stringify(obj, function (key, value) {
          if (value && Array.isArray(value) && value.tag !== undefined) {
            var r = {};
            r.values = value.slice();
            r.tag = value.tag;
            r.type = 'wvariant';
            return r;
          } else {
            return value;
          }
        });
        return { data: JSON.parse(data), type: 'wevent' };
      })
    |}
    ];
    let decode: Js.Json.t => array(Config.route) = [%bs.raw
      {|
      (function(result) {
        if(result && typeof(result) === 'object' && result.type === 'wevent') {
          var serialized = result.serialized || JSON.stringify(result.data);
          return JSON.parse(serialized, (key, value) => {
            if (value && typeof (value) === 'object' && value.type === 'wvariant') {
              var values = value.values;
              values.tag = value.tag;
              return values;
            } else {
              return value;
            }
          });
        } else {
          return result;
        }
      })
    |}
    ];
  };
};