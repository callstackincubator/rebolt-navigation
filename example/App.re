open Navigation;

module Main = {
  let component = ReasonReact.statelessComponent("App");
  let make = _children => {
    ...component,
    render: _self =>
      <StackNavigator initialRoute=Config.TabExample>
        ...(
             (~currentRoute, ~navigation) =>
               switch (currentRoute) {
               | Config.TabExample => <TabExample navigation />
               | Config.Home => <Home navigation />
               | Config.Admin => <Admin navigation />
               | _ => <TabExample navigation />
               }
           )
      </StackNavigator>,
  };
};

let app = () => <Main />;