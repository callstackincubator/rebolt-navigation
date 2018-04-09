module Config = {
  type route =
    | Feed
    | Admin
    | Likes
    | Home
    | About
    | TabExample;
};

/** todo figure out namespacing this */
module ReactNavigation = ReRoute.CreateNavigation(Config);

module StackNavigator = ReactNavigation.StackNavigator;

module TabNavigator = ReactNavigation.TabNavigator;

module Screen = ReactNavigation.Screen;