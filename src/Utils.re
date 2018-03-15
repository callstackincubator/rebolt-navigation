module UUID = {
  let count = ref(0);
  let generate = () => {
    count := count^ + 1;
    "id-"
    ++ (Js.Date.now() |> Js.Date.fromFloat |> Js.Date.toString)
    ++ string_of_int(count^);
  };
};

module StringMap =
  Map.Make(
    {
      type t = string;
      let compare = compare;
    }
  );
