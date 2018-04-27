module CreateTabNavigator:
  (Config: {type route;}) =>
  {
    module TabNavigator: {
      type tabItem =
        | Label(string)
        | Icon(BsReactNative.Image.imageSource)
        | IconWithActiveIcon(
            BsReactNative.Image.imageSource,
            BsReactNative.Image.imageSource,
          )
        | LabelWithIcon(string, BsReactNative.Image.imageSource)
        | LabelWithIconAndActiveIcon(
            string,
            BsReactNative.Image.imageSource,
            BsReactNative.Image.imageSource,
          );
      type currentRoute = Config.route;
      type jumpTo = Config.route => unit;
      type options = {
        tabItem,
        labelColor: option(string),
        activeLabelColor: option(string),
      };
      type screenConfig = {
        route: Config.route,
        tabItem,
        labelColor: option(string),
        activeLabelColor: option(string),
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
        indicatorColor: option(string),
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
            ~tabItem: tabItem,
            ~labelColor: string=?,
            ~activeLabelColor: string=?,
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
          (
            ~tabItem: tabItem,
            ~labelColor: option(string),
            ~activeLabelColor: option(string),
            ~isActive: bool,
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
    };
  };