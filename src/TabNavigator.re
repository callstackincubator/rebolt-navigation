open BsReactNative;

module Styles = {
  open Style;
  type textSize =
    | Small
    | Regular;
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
      borderTopWidth(StyleSheet.hairlineWidth),
      borderTopColor(String("rgba(0, 0, 0, 0.3)")),
    ]);
  let tabBarItemContainer =
    style([
      flex(1.),
      justifyContent(Center),
      alignItems(
        switch (Platform.os()) {
        | Platform.Android => Stretch
        | _ => Center
        },
      ),
    ]);
  let tabBarItem = style([alignItems(Center)]);
  let tabBarItemIcon = style([height(Pt(20.)), width(Pt(20.))]);
  let tabBarItemText = (~isActive, ~textSize) =>
    style([
      bottom(
        Pt(
          switch (textSize) {
          | Small => (-6.)
          | Regular => 0.
          },
        ),
      ),
      color(String(isActive ? "#2180f7" : "#8c8c8c")),
      fontSize(
        Float(
          switch (textSize) {
          | Small => 10.0
          | Regular => 13.0
          },
        ),
      ),
    ]);
};

module CreateTabNavigator = (Config: {type route;}) => {
  module TabNavigator = {
    type currentRoute = Config.route;
    type jumpTo = Config.route => unit;
    type options = {
      label: string,
      iconSource: option(Image.imageSource),
      activeIconSource: option(Image.imageSource),
    };
    type screenConfig = {
      route: Config.route,
      label: string,
      iconSource: option(Image.imageSource),
      activeIconSource: option(Image.imageSource),
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
    module TabBarItem = {
      let component = ReasonReact.statelessComponent("TabBarItem");
      let make =
          (
            ~label,
            ~iconSource: option(Image.imageSource),
            ~activeIconSource: option(Image.imageSource),
            ~isActive,
            _children,
          ) => {
        ...component,
        render: _self =>
          switch (label, iconSource, activeIconSource) {
          | (label, Some(iconSource), Some(activeIconSource)) =>
            <View style=Styles.tabBarItem>
              (
                isActive ?
                  <Image
                    source=activeIconSource
                    style=Styles.tabBarItemIcon
                  /> :
                  <Image source=iconSource style=Styles.tabBarItemIcon />
              )
              <Text style=(Styles.tabBarItemText(~isActive, ~textSize=Small))>
                (ReasonReact.stringToElement(label))
              </Text>
            </View>
          | (label, Some(iconSource), None) =>
            <View style=Styles.tabBarItem>
              <Image source=iconSource style=Styles.tabBarItemIcon />
              <Text style=(Styles.tabBarItemText(~isActive, ~textSize=Small))>
                (ReasonReact.stringToElement(label))
              </Text>
            </View>
          | (label, None, Some(activeIconSource)) =>
            <View style=Styles.tabBarItem>
              <Image source=activeIconSource style=Styles.tabBarItemIcon />
              <Text style=(Styles.tabBarItemText(~isActive, ~textSize=Small))>
                (ReasonReact.stringToElement(label))
              </Text>
            </View>
          | (label, None, None) =>
            <Text style=(Styles.tabBarItemText(~isActive, ~textSize=Regular))>
              (ReasonReact.stringToElement(label))
            </Text>
          },
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
                   <TouchableWithoutFeedback
                     key=(string_of_int(index))
                     onPress=(_e => tabBarProps.jumpTo(screen.route))>
                     <View style=Styles.tabBarItemContainer>
                       <TabBarItem
                         label=screen.label
                         isActive
                         iconSource=screen.iconSource
                         activeIconSource=screen.activeIconSource
                       />
                     </View>
                   </TouchableWithoutFeedback>;
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
        screens:
          routes
          |> Array.map(route =>
               {route, label: "", iconSource: None, activeIconSource: None}
             ),
        currentRoute: initialRoute,
      },
      reducer: (action, state) =>
        switch (action) {
        | JumpTo(route) =>
          if (route !== state.currentRoute) {
            ReasonReact.Update({...state, currentRoute: route});
          } else {
            ReasonReact.NoUpdate;
          }
        | SetOptions({label, iconSource, activeIconSource}, index) =>
          let screens = Js.Array.copy(state.screens);
          screens[index] = {
            ...screens[index],
            label,
            iconSource,
            activeIconSource,
          };
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
                         jumpTo: route => self.send(JumpTo(route)),
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
                  jumpTo: route => self.send(JumpTo(route)),
                },
              )
            | None =>
              <TabBar
                tabBarProps={
                  screens: self.state.screens,
                  currentRoute: self.state.currentRoute,
                  jumpTo: route => self.send(JumpTo(route)),
                }
              />
            }
          )
        </View>,
    };
    module Screen = {
      let component = ReasonReact.statelessComponent("Screen");
      let make =
          (
            ~navigation,
            ~label,
            ~iconSource: option(Image.imageSource)=?,
            ~activeIconSource: option(Image.imageSource)=?,
            children,
          ) => {
        ...component,
        didMount: _self => {
          navigation.setOptions({label, iconSource, activeIconSource});
          ReasonReact.NoUpdate;
        },
        render: _self =>
          navigation.isActive ?
            <View style=Styles.tabContainer> (children()) </View> :
            ReasonReact.nullElement,
      };
    };
  };
};