module Screens = {
  let homeScreen = StackNavigator.makeScreen();
  let adminScreen = StackNavigator.makeScreen();
  let makeHomeScreen = () => {
    ...homeScreen,
    initialState: () => false,
    render: (_, send) => <Home push=(() => send(true)) pop=(() => ()) />,
    reducer: (_, x) => x,
    key: "Home",
    popChild: (_) => false,
    renderChild: (state, _) =>
      if (state) {
        Some(Screen(makeAdminScreen()));
      } else {
        None;
      }
  }
  and makeAdminScreen = () => {
    ...adminScreen,
    initialState: () => false,
    render: (_, send) => <Admin push=(() => send(true)) pop=(() => ()) />,
    reducer: (_, x) => x,
    key: "Home",
    popChild: (_) => false,
    renderChild: (state, _) =>
      if (state) {
        Some(Screen(makeHomeScreen()));
      } else {
        None;
      }
  };
};

module Main = {
  let component = ReasonReact.statelessComponent("App");
  let make = _children => {
    ...component,
    render: _self =>
      <StackNavigator initialScreen=(Screens.makeHomeScreen()) />
  };
};

let app = () => <Main />;
