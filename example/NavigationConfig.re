module Config = {
  type route =
    | Welcome
    | Feed
    | Admin
    | Likes
    | Home
    | About
    | TabExample
    | CustomTabBarExample;
};

include ReRoute.CreateNavigation(Config);