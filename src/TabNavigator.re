open BsReactNative;

module Styles = {
  open Style;
  let tabContainer = style([flex(1.)]);
  let screenContainer = style([flex(1.)]);
};

module CreateTabNavigator = (Config: {type route;}) => {
  module TabNavigator = {
    type action =
      | GoToRoute(Config.route);
    type state = {
      routes: array(Config.route),
      currentRoute: Config.route,
    };
    type navigation = {goToRoute: Config.route => unit};
    let component = ReasonReact.reducerComponent("TabNavigator");
    let make =
        (~initialRoute, ~routes, ~renderTabBar, ~screenStyle=?, children) => {
      ...component,
      initialState: () => {routes, currentRoute: initialRoute},
      reducer: (action, state) =>
        switch (action) {
        | GoToRoute(route) =>
          if (route !== state.currentRoute) {
            ReasonReact.Update({...state, currentRoute: route});
          } else {
            ReasonReact.NoUpdate;
          }
        },
      render: self =>
        <View style=Styles.tabContainer>
          (
            self.state.routes
            |> Array.mapi((index, route) =>
                 route !== self.state.currentRoute ?
                   ReasonReact.nullElement :
                   <View
                     key=(string_of_int(index))
                     style=Style.(
                             concat([
                               Styles.screenContainer,
                               switch (screenStyle) {
                               | Some(screenStyle) => screenStyle
                               | None => style([])
                               },
                             ])
                           )>
                     (
                       children(
                         ~currentRoute=route,
                         ~navigation={
                           goToRoute: route => self.send(GoToRoute(route)),
                         },
                       )
                     )
                   </View>
               )
            |> ReasonReact.arrayToElement
          )
          (
            renderTabBar(
              ~routes,
              ~navigation={goToRoute: route => self.send(GoToRoute(route))},
              ~currentRoute=self.state.currentRoute,
            )
          )
        </View>,
    };
  };
};