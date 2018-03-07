module Config = {
  type route =
    | Admin
    | Home;
};

/** todo figure out namespacing this */
module ReactNavigation = ReRoute.CreateNavigation(Config);

module StackNavigator = ReactNavigation.StackNavigator;

module Header = ReactNavigation.Header;
