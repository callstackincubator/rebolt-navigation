module CreateTabNavigator:
  (Config: {type route;}) =>
  {
    module TabNavigator: {
      type tabItemProps = {isActive: bool};
      type currentRoute = Config.route;
      type jumpTo = Config.route => unit;
      type tabItem = tabItemProps => ReasonReact.reactElement
      and tabBarProps = {
        screens,
        currentRoute,
        jumpTo,
        indicatorColor: option(string),
      }
      and options = {tabItem}
      and screenConfig = {
        route: Config.route,
        tabItem,
      }
      and screens = array(screenConfig);
      type navigation = {
        screens,
        currentRoute,
        jumpTo,
        setOptions: options => unit,
        isActive: bool,
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
          ~safeAreaViewBackgroundColor: string=?,
          ~indicatorColor: string=?,
          ~onNavigationReady: navigation => unit=?,
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
            ~tabItem: tabItemProps => ReasonReact.reactElement,
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
        module Item: {
          let make:
            (
              ~label: string,
              ~icon: Rebolt.Image.imageSource=?,
              ~style: Rebolt.Style.t=?,
              'a
            ) =>
            ReasonReact.componentSpec(
              ReasonReact.stateless,
              ReasonReact.stateless,
              ReasonReact.noRetainedProps,
              ReasonReact.noRetainedProps,
              ReasonReact.actionless,
            );
        };
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
    };
  };
