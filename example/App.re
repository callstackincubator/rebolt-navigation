/**
 * Route and Navigation types are kept in a separate module to
 * handle circular references between modules
 */
open Config;

module Stack =
  StackNavigator.Create({
    open StackNavigator;

    /**
     * StackNavigator requires `route` type to be defined.
     */
    type route = Config.route;

    /**
     * Initial route to start with. Has to be one of `route` variants.
     */
    let initialRoute = Home;

    /**
     * Returns a screen for a given route and its options.
     *
     * To declare options, you call `StackNavigator.screenOptions` and provide
     * same keys as `navigationOptions` of React Navigation.
     *
     * This is to allow optional fields to be provided.
     */
    let getScreen = (route, navigation) =>
      switch (route) {
      | Home => (<Screen navigation />, screenOptions(~title="Home", ()))
      | UserDetails(userId) => (
          <Screen navigation text={"Browsing profile of: " ++ userId} />,
          screenOptions(~title="Hello " ++ userId, ()),
        )
      };
  });

/**
 * Exporting application entry-point, see `index.js` for details
 */
let app = Stack.navigator;