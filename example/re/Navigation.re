module Config = {
  type route =
    | Admin
    | Home;
};

module ReactNavigation = ReRoute.CreateNavigation(Config);

module StackNavigator = ReactNavigation.StackNavigator;
