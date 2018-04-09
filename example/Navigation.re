module Config = {
  type route =
    | Feed
    | Admin
    | Likes
    | Home
    | About
    | TabExample;
};

include ReRoute.CreateNavigation(Config);