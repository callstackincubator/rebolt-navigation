module CreateTabNavigator:
  (Config: {type route;}) =>
  {
    module TabNavigator: {
      type currentRoute = Config.route;
      type jumpTo = Config.route => unit;
      type options = {label: string};
      type screenConfig = {
        route: Config.route,
        label: string,
      };
      type screens = array(screenConfig);
      type navigation = {
        screens,
        currentRoute,
        jumpTo,
        setOptions: options => unit,
        isActive: bool,
      };
      type tabBarProps = {
        screens,
        currentRoute,
        jumpTo,
      };
      type action =
        | JumpTo(Config.route)
        | SetOptions(options, int);
      type state = {
        screens,
        currentRoute,
      };
      let make:
        (
          ~initialRoute: currentRoute,
          ~routes: array(Config.route),
          ~renderTabBar: (~tabBarProps: tabBarProps) =>
                         ReasonReact.reactElement
                           =?,
          (~navigation: navigation) => ReasonReact.reactElement
        ) =>
        ReasonReact.componentSpec(
          state,
          state,
          ReasonReact.noRetainedProps,
          ReasonReact.noRetainedProps,
          action,
        );
      module Screen: {
        let make:
          (
            ~navigation: navigation,
            ~label: string,
            unit => ReasonReact.reactElement
          ) =>
          ReasonReact.componentSpec(
            ReasonReact.stateless,
            ReasonReact.stateless,
            ReasonReact.noRetainedProps,
            ReasonReact.noRetainedProps,
            ReasonReact.actionless,
          );
      };
      module TabBar: {
        let make:
          (~tabBarProps: tabBarProps, 'a) =>
          ReasonReact.componentSpec(
            ReasonReact.stateless,
            ReasonReact.stateless,
            ReasonReact.noRetainedProps,
            ReasonReact.noRetainedProps,
            ReasonReact.actionless,
          );
      };
      module TabBarItem: {
        let make:
          (~label: string, ~isActive: bool, 'a) =>
          ReasonReact.componentSpec(
            ReasonReact.stateless,
            ReasonReact.stateless,
            ReasonReact.noRetainedProps,
            ReasonReact.noRetainedProps,
            ReasonReact.actionless,
          );
      };
    };
  };