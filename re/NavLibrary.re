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
        children
      </View>
  };
};

module CreateNavigation = (Config: NavigationConfig) => {
  module StackNavigator = {
    type action =
      | Push(Config.route)
      | Pop;
    type screen = {
      route: Config.route,
      key: int
    };
    type state = {screens: list(screen)};
    type navigation = {send: action => unit};
    let component = ReasonReact.reducerComponent("CallstackStackNavigator");
    let make = (~initialRoute, children) => {
      ...component,
      initialState: () => {screens: [{route: initialRoute, key: 0}]},
      reducer: (action, state) =>
        switch action {
        | Push(route) =>
          let screen = {route, key: List.length(state.screens)};
          ReasonReact.Update({screens: [screen, ...state.screens]});
        | Pop =>
          List.(
            length(state.screens) > 1 ?
              ReasonReact.Update({screens: tl(state.screens)}) :
              ReasonReact.NoUpdate
          )
        },
      render: self => {
        let navigation: navigation = {send: self.send};
        self.state.screens
        |> List.rev_map(screen =>
             <SceneView key=(string_of_int(screen.key))>
               ...(children(~currentRoute=screen.route, ~navigation))
             </SceneView>
           )
        |> Array.of_list
        |> ReasonReact.arrayToElement;
      }
    };
  };
};
