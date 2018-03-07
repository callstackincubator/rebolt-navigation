module Config = {
  type route =
    | Admin
    | Home;
};

module ReactNavigation = NavLibrary.CreateNavigation(Config);

module StackNavigator = ReactNavigation.StackNavigator;
