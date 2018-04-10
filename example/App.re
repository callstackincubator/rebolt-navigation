open Navigation;

module Main = {
  let component = ReasonReact.statelessComponent("App");
  let make = _children => {
    ...component,
    render: _self =>
      <StackNavigator initialRoute=Config.Admin>
        ...(
             (~currentRoute, ~navigation) =>
               switch (currentRoute) {
               | Config.Admin => <Admin navigation />
               | Config.Home => <Home navigation />
               }
           )
      </StackNavigator>,
  };
};

let app = () => <Main />;