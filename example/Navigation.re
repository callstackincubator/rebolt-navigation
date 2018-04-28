module Config = {
  type route =
    | Feed
    | Admin
    | Likes
    | Home
    | About
    | TabExample;

  let stateForUrl = (state, url) => state;
};

include ReRoute.CreateNavigation(Config);