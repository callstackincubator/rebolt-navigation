module CreateNavigation = (Config: ReRouteTypes.Config) => {
  include StackNavigator.CreateStackNavigator(Config);
  include TabNavigator.CreateTabNavigator(Config);
};