module Config = {
  type route =
    | Admin
    | Home;
};

include ReRoute.CreateNavigation(Config);