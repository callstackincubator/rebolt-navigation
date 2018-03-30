/**
 * React Navigation inspired UUID module
 * https://github.com/react-navigation/react-navigation/blob/master/src/routers/KeyGenerator.js
 */
module UUID = {
  let count = ref(0);
  let generate = () => {
    count := count^ + 1;
    "id-"
    ++ (Js.Date.now() |> Js.Date.fromFloat |> Js.Date.toString)
    ++ string_of_int(count^);
  };
};

/**
 * Some common Array operations used within ReRoute extracted to one place
 */
module ReArray = {
  let append = (el, idx, arr) => {
    let copied = Js.Array.copy(arr);
    let _ignored =
      copied |> Js.Array.spliceInPlace(~pos=idx, ~remove=0, ~add=[|el|]);
    copied;
  };
  let remove = (idx, arr) => {
    let copied = Js.Array.copy(arr);
    let _ignored =
      copied |> Js.Array.spliceInPlace(~pos=idx, ~remove=idx, ~add=[||]);
    copied;
  };
};

let option_map = (fn, opt_value) =>
  switch (opt_value) {
  | None => None
  | Some(value) => Some(fn(value))
  };