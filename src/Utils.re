/**
 * Source:
 * https://github.com/jasonrose/clj-collection-apis-reasonml/blob/master/src/Clj_list.re#L91
 */
let rec dropWhile = (predicate, list) =>
  switch list {
  | [] => []
  | [a] =>
    if (predicate(a)) {
      [];
    } else {
      [a];
    }
  | [a, ...rest] =>
    if (predicate(a)) {
      dropWhile(predicate, rest);
    } else {
      list;
    }
  };
