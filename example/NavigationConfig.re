module Config = {
  type route =
    | Welcome
    | Feed
    | Admin
    | Likes
    | Home
    | UserProfile
    | About
    | TabExample
    | ContactList
    | Messages
    | CustomTabBarExample;
};

include RerouteNative.ReRoute.CreateNavigation(Config);
