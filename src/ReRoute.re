module CreateNavigation = (Config: {type route;}) => {
  include StackNavigator.CreateStackNavigator(Config);
  include TabNavigator.CreateTabNavigator(Config);
  include Persistence.CreatePersistor(Config);
};