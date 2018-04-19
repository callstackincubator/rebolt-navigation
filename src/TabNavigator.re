open BsReactNative;

module Styles = {
  open Style;
  let tabContainer = style([flex(1.)]);
  let screenContainer = isActive =>
    isActive ?
      style([
        position(Absolute),
        top(Pt(0.)),
        right(Pt(0.)),
        bottom(Pt(0.)),
        left(Pt(0.)),
      ]) :
      style([
        position(Absolute),
        top(Pt(0.)),
        right(Pt(0.)),
        bottom(Pt(0.)),
        left(Pt(0.)),
        opacity(Float(0.)),
      ]);
  let tabBar =
    style([
      flexDirection(Row),
      backgroundColor(String("#f7f7f7")),
      height(Pt(49.)),
      position(Absolute),
      left(Pt(0.0)),
      right(Pt(0.0)),
      bottom(Pt(0.0)),
      borderTopWidth(1.),
      borderTopColor(String("#d7d7d7")),
    ]);
  let tabBarItem =
    style([flex(1.), justifyContent(Center), alignItems(Center)]);
  let tabBarItemText = isActive =>
    style([color(String(isActive ? "#2180f7" : "#8c8c8c"))]);
};

module CreateTabNavigator = (Config: {type route;}) => {
  module TabNavigator = {
    type currentRoute = Config.route;
    type goTo = Config.route => unit;
    type options = {label: string};
    type index = int;
    type setOptions = options => unit;
    type screenConfig = {
      route: Config.route,
      label: string,
    };
    type screens = array(screenConfig);
    type navigation = {
      screens,
      currentRoute,
      goTo,
      setOptions,
      isActive: bool,
    };
    type tabBarProps = {
      screens,
      currentRoute,
      goTo,
    };
    type action =
      | GoTo(Config.route)
      | SetOptions(options, index);
    type state = {
      screens,
      currentRoute,
    };
    module TabBarItem = {
      let component = ReasonReact.statelessComponent("TabBarItem");
      let make = (~label, ~isActive, _children) => {
        ...component,
        render: _self =>
          <Text style=(Styles.tabBarItemText(isActive))>
            (ReasonReact.stringToElement(label))
          </Text>,
      };
    };
    module TabBar = {
      let component = ReasonReact.statelessComponent("TabBar");
      let make = (~tabBarProps: tabBarProps, _children) => {
        ...component,
        render: _self =>
          <View style=Styles.tabBar>
            (
              tabBarProps.screens
              |> Array.mapi((index, screen) => {
                   let isActive = tabBarProps.currentRoute === screen.route;
                   <TouchableOpacity
                     key=(string_of_int(index))
                     style=Styles.tabBarItem
                     onPress=(_e => tabBarProps.goTo(screen.route))>
                     <TabBarItem label=screen.label isActive />
                   </TouchableOpacity>;
                 })
              |> ReasonReact.arrayToElement
            )
          </View>,
      };
    };
    let component = ReasonReact.reducerComponent("TabNavigator");
    let make = (~initialRoute, ~routes, ~renderTabBar=?, children) => {
      ...component,
      initialState: () => {
        screens: routes |> Array.map(route => {route, label: ""}),
        currentRoute: initialRoute,
      },
      reducer: (action, state) =>
        switch (action) {
        | GoTo(route) =>
          if (route !== state.currentRoute) {
            ReasonReact.Update({...state, currentRoute: route});
          } else {
            ReasonReact.NoUpdate;
          }
        | SetOptions({label}, index) =>
          let screens = Js.Array.copy(state.screens);
          screens[index] = {...screens[index], label};
          ReasonReact.Update({...state, screens});
        },
      render: self =>
        <View style=Styles.tabContainer>
          (
            self.state.screens
            |> Array.mapi((index, screen) => {
                 let isActive = self.state.currentRoute === screen.route;
                 <View
                   key=(string_of_int(index))
                   style=(Styles.screenContainer(isActive))
                   pointerEvents=(isActive ? `auto : `none)>
                   (
                     children(
                       ~navigation={
                         goTo: route => self.send(GoTo(route)),
                         currentRoute: screen.route,
                         screens: self.state.screens,
                         setOptions: options =>
                           self.send(SetOptions(options, index)),
                         isActive,
                       },
                     )
                   )
                 </View>;
               })
            |> ReasonReact.arrayToElement
          )
          (
            switch (renderTabBar) {
            | Some(renderTabBar) =>
              renderTabBar(
                ~tabBarProps={
                  screens: self.state.screens,
                  currentRoute: self.state.currentRoute,
                  goTo: route => self.send(GoTo(route)),
                },
              )
            | None =>
              <TabBar
                tabBarProps={
                  screens: self.state.screens,
                  currentRoute: self.state.currentRoute,
                  goTo: route => self.send(GoTo(route)),
                }
              />
            }
          )
        </View>,
    };
    module Screen = {
      let component = ReasonReact.statelessComponent("Screen");
      let make = (~navigation, ~label, children) => {
        ...component,
        didMount: _self => {
          navigation.setOptions({label: label});
          ReasonReact.NoUpdate;
        },
        render: _self =>
          navigation.isActive ?
            <View style=Styles.tabContainer> ...children </View> :
            ReasonReact.nullElement,
      };
    };
  };
};