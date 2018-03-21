open BsReactNative;

type config = {title: option(string)};

type screenConfig = {header: config};

let default = {title: None};

module FloatingHeader = {
  let component = ReasonReact.statelessComponent("FloatingHeader");
  let (appBarHeight, statusBarHeight) =
    Platform.(
      switch (os()) {
      | Platform.IOS(_) => (44.0, 20.0)
      | Platform.Android => (56.0, 0.0)
      }
    );
  let make = (~screens: array(screenConfig), _children) => {
    ...component,
    render: _self =>
      <View
        style=Style.(
                style([
                  backgroundColor("#FFF"),
                  height(Pt(appBarHeight +. statusBarHeight))
                ])
              )>
        (
          screens
          |> Array.mapi((idx: int, {header}) =>
               <Text key=(string_of_int(idx))>
                 (
                   ReasonReact.stringToElement(
                     Js.Option.getWithDefault("", header.title)
                   )
                 )
               </Text>
             )
          |> ReasonReact.arrayToElement
        )
      </View>
  };
};