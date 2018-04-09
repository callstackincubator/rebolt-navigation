open ReRouteTypes;

module CreateNavigation = (Config: NavigationConfig) => {
  include StackNavigator.CreateStackNavigator(Config);
  include TabNavigator.CreateTabNavigator(Config);
};