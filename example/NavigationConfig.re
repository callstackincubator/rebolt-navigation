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
    | CustomTabBarExample
    | CustomHome
    | CustomMessages
    | CustomProfile
    | CustomProfileDetails
    | CustomProfileStats;
};

include RerouteNative.ReRoute.CreateNavigation(Config);
