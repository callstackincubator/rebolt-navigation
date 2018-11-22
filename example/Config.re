type route =
  | Home
  | UserDetails(string);
type navigation = StackNavigator.navigation(route);