open ReRouteTypes;

module CreateNavigation = (Config: NavigationConfig) => {
  include StackNavigator.CreateStackNavigator(Config);
};