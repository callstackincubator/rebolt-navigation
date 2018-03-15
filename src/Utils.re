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
