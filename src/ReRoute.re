open BsReactNative;

module type NavigationConfig = {type route;};

module SceneView = {
  let component = ReasonReact.statelessComponent("NavSceneView");
  let make = children => {
    ...component,
    render: _self =>
      <View
        style=Style.(
                style([
                  position(Absolute),
                  top(Pt(0.0)),
                  left(Pt(0.0)),
                  right(Pt(0.0)),
                  bottom(Pt(0.0)),
                  backgroundColor("#ffffff")
                ])
              )>
        ...children
      </View>
  };
};

module StringMap =
  Map.Make(
    {
      type t = string;
      let compare = compare;
    }
  );

module CreateNavigation = (Config: NavigationConfig) => {
  module StackNavigator = {
    type headerConfig = {title: option(string)};
    type screenKey = string;
    type screenConfig = {
      route: Config.route,
      key: screenKey
    };
    type state = {
      screens: list(screenConfig),
      headers: StringMap.t(headerConfig)
    };
    type action =
      | Push(Config.route)
      | SetHeaderOptions(screenKey, headerConfig)
      | Pop;
    type navigation = {
      send: action => unit,
      key: screenKey
    };
    module HeaderImpl = {
			let component = ReasonReact.statelessComponent("NavHeader");
			let def = (opt, def) => switch (opt) {
				| Some(value) => value
				| None => def
			};
      let make = (~config: headerConfig, _children) => {
        ...component,
        render: _self =>
					<View>
						<Text>(ReasonReact.stringToElement(def(config.title, "")))</Text>
          </View>
      };
    };
    let component = ReasonReact.reducerComponent("NavStackNavigator");
    let make = (~initialRoute, children) => {
      ...component,
      initialState: () => {
        screens: [{route: initialRoute, key: "0"}],
        headers: StringMap.empty
      },
      reducer: (action, state) =>
        switch action {
        | Push(route) =>
          let screen = {route, key: string_of_int(List.length(state.screens))};
          ReasonReact.Update({...state, screens: [screen, ...state.screens]});
        | Pop =>
          List.(
            length(state.screens) > 1 ?
              ReasonReact.Update({...state, screens: tl(state.screens)}) :
              ReasonReact.NoUpdate
          )
        | SetHeaderOptions(screenKey, options) =>
          ReasonReact.Update({
            ...state,
            headers: StringMap.add(screenKey, options, state.headers)
          })
        },
      render: self =>
        self.state.screens
        |> List.rev_map((screen: screenConfig) =>
             <SceneView key=screen.key>
               (
                 switch (StringMap.find(screen.key, self.state.headers)) {
                 | config => <HeaderImpl config />
                 | exception Not_found => <View />
                 }
               )
               <View style=Style.(style([flex(1.0)]))>
                 (
                   children(
                     ~currentRoute=screen.route,
                     ~navigation={send: self.send, key: screen.key}
                   )
                 )
               </View>
             </SceneView>
           )
        |> Array.of_list
        |> ReasonReact.arrayToElement
    };
  };
  module Header = {
    open StackNavigator;
    let component = ReasonReact.statelessComponent("CallstackHeader");
    let make = (~navigation: navigation, ~title=?, _children) => {
      ...component,
      didMount: _self => {
        navigation.send(SetHeaderOptions(navigation.key, {title: title}));
        ReasonReact.NoUpdate;
      },
      render: _self => <View />
    };
  };
};
