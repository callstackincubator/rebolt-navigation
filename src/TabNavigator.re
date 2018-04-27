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
  let tabBarContainer =
      (safeAreaViewBackgroundColor: option(string), renderTabBar) =>
    style([
      flex(1.),
      backgroundColor(
        switch (
          safeAreaViewBackgroundColor,
          renderTabBar:
            option((~tabBarProps: 'a) => ReasonReact.reactElement),
        ) {
        | (None, None) => String("#f7f7f7")
        | (None, Some(_r)) => String("transparent")
        | (Some(safeAreaViewBackgroundColor), _) =>
          String(safeAreaViewBackgroundColor)
        },
      ),
    ]);
  let tabBar = hasIcon =>
    switch (Platform.os()) {
    | Platform.Android =>
      style([
        flexDirection(Row),
        backgroundColor(String("#fff")),
        height(Pt(hasIcon ? 72. : 48.)),
        position(Absolute),
        left(Pt(0.0)),
        right(Pt(0.0)),
        top(Pt(0.0)),
        elevation(4.),
        shadowOpacity(0.1),
        zIndex(0),
      ])
    | _ =>
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
      ])
    };
  let tabBarIndicator = (denominator, itemIndex, indicatorColor) => {
    let itemWidth =
      float_of_int(Dimensions.get(`window)##width) /. denominator;
    style([
      position(Absolute),
      bottom(Pt(0.)),
      height(Pt(2.)),
      left(Pt(itemWidth *. float_of_int(itemIndex))),
      backgroundColor(
        String(
          switch (indicatorColor) {
          | Some(indicatorColor) => indicatorColor
          | None => "blue"
          },
        ),
      ),
      width(Pt(itemWidth)),
    ]);
  };
  let tabBarItemContainer =
    switch (Platform.os()) {
    | Platform.Android =>
      style([flex(1.), justifyContent(Center), alignItems(Center)])
    | _ => style([flex(1.), justifyContent(Center), alignItems(Center)])
    };
  let tabBarItem = style([alignItems(Center)]);
  let tabBarItemIcon =
    switch (Platform.os()) {
    | Platform.Android =>
      style([
        height(Pt(24.)),
        width(Pt(24.)),
        padding(Pt(0.0)),
        margin(Pt(0.0)),
      ])
    | _ => style([height(Pt(20.)), width(Pt(20.))])
    };
  let tabBarItemText =
      (
        ~isActive,
        ~textSize,
        ~labelColor: option(string),
        ~activeLabelColor: option(string),
      ) =>
    switch (Platform.os()) {
    | Platform.Android =>
      style([
        paddingTop(
          switch (textSize) {
          | Small => Pt(10.)
          | Regular => Pt(0.)
          },
        ),
        bottom(
          switch (textSize) {
          | Small => Pt(4.)
          | Regular => Pt(0.)
          },
        ),
        margin(Pt(0.)),
        color(
          switch (labelColor, activeLabelColor) {
          | (Some(labelColor), Some(activeLabelColor)) =>
            String(isActive ? activeLabelColor : labelColor)
          | (None, None) => String(isActive ? "#2180f7" : "#8c8c8c")
          | (None, Some(activeLabelColor)) =>
            String(isActive ? activeLabelColor : "#8c8c8c")
          | (Some(labelColor), None) =>
            String(isActive ? "#2180f7" : labelColor)
          },
        ),
        fontSize(Float(14.0)),
      ])
    | _ =>
      style([
        bottom(
          Pt(
            switch (textSize) {
            | Small => (-6.)
            | Regular => 0.
            },
          ),
        ),
        color(
          switch (labelColor, activeLabelColor) {
          | (Some(labelColor), Some(activeLabelColor)) =>
            String(isActive ? activeLabelColor : labelColor)
          | (None, None) => String(isActive ? "#2180f7" : "#8c8c8c")
          | (None, Some(activeLabelColor)) =>
            String(isActive ? activeLabelColor : "#8c8c8c")
          | (Some(labelColor), None) =>
            String(isActive ? "#2180f7" : labelColor)
          },
        ),
        fontSize(
          Float(
            switch (textSize) {
            | Small => 10.0
            | Regular => 13.0
            },
          ),
        ),
      ])
    };
};

module CreateTabNavigator = (Config: {type route;}) => {
  module TabNavigator = {
    type currentRoute = Config.route;
    type jumpTo = Config.route => unit;
    type options = {
      label: string,
      labelColor: option(string),
      activeLabelColor: option(string),
      iconSource: option(Image.imageSource),
      activeIconSource: option(Image.imageSource),
    };
    type screenConfig = {
      route: Config.route,
      label: string,
      labelColor: option(string),
      activeLabelColor: option(string),
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
      indicatorColor: option(string),
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
            ~labelColor: option(string),
            ~activeLabelColor: option(string),
            ~iconSource: option(Image.imageSource),
            ~activeIconSource: option(Image.imageSource),
            ~isActive,
            _children,
          ) => {
        ...component,
        render: _self => {
          let itemText =
            switch (Platform.os()) {
            | Platform.Android => String.uppercase(label)
            | _ => label
            };
          switch (itemText, iconSource, activeIconSource) {
          | (itemText, Some(iconSource), Some(activeIconSource)) =>
            <View style=Styles.tabBarItem>
              (
                isActive ?
                  <Image
                    source=activeIconSource
                    style=Styles.tabBarItemIcon
                  /> :
                  <Image source=iconSource style=Styles.tabBarItemIcon />
              )
              <Text
                style=(
                  Styles.tabBarItemText(
                    ~isActive,
                    ~textSize=Small,
                    ~labelColor,
                    ~activeLabelColor,
                  )
                )>
                (ReasonReact.stringToElement(itemText))
              </Text>
            </View>
          | (itemText, Some(iconSource), None) =>
            <View style=Styles.tabBarItem>
              <Image source=iconSource style=Styles.tabBarItemIcon />
              <Text
                style=(
                  Styles.tabBarItemText(
                    ~isActive,
                    ~textSize=Small,
                    ~labelColor,
                    ~activeLabelColor,
                  )
                )>
                (ReasonReact.stringToElement(itemText))
              </Text>
            </View>
          | (itemText, None, Some(activeIconSource)) =>
            <View style=Styles.tabBarItem>
              <Image source=activeIconSource style=Styles.tabBarItemIcon />
              <Text
                style=(
                  Styles.tabBarItemText(
                    ~isActive,
                    ~textSize=Small,
                    ~labelColor,
                    ~activeLabelColor,
                  )
                )>
                (ReasonReact.stringToElement(itemText))
              </Text>
            </View>
          | (itemText, None, None) =>
            <Text
              style=(
                Styles.tabBarItemText(
                  ~isActive,
                  ~textSize=Regular,
                  ~labelColor,
                  ~activeLabelColor,
                )
              )>
              (ReasonReact.stringToElement(itemText))
            </Text>
          };
        },
      };
    };
    module TabBar = {
      let component = ReasonReact.statelessComponent("TabBar");
      let make = (~tabBarProps: tabBarProps, _children) => {
        ...component,
        render: _self => {
          let hasIcon =
            ListLabels.exists(
              screen =>
                switch (screen.iconSource, screen.activeIconSource) {
                | (None, None) => false
                | _ => true
                },
              ArrayLabels.to_list(tabBarProps.screens),
            );
          <View style=(Styles.tabBar(hasIcon))>
            (
              switch (Platform.os()) {
              | Platform.Android =>
                tabBarProps.screens
                |> Array.mapi((index, screen) => {
                     let isActive = tabBarProps.currentRoute === screen.route;
                     isActive ?
                       <View
                         key=(string_of_int(index))
                         style=(
                           Styles.tabBarIndicator(
                             float_of_int(Array.length(tabBarProps.screens)),
                             index,
                             tabBarProps.indicatorColor,
                           )
                         )
                       /> :
                       ReasonReact.nullElement;
                   })
                |> ReasonReact.arrayToElement
              | _ => ReasonReact.nullElement
              }
            )
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
                         labelColor=screen.labelColor
                         activeLabelColor=screen.activeLabelColor
                         isActive
                         iconSource=screen.iconSource
                         activeIconSource=screen.activeIconSource
                       />
                     </View>
                   </TouchableWithoutFeedback>;
                 })
              |> ReasonReact.arrayToElement
            )
          </View>;
        },
      };
    };
    let component = ReasonReact.reducerComponent("TabNavigator");
    let make =
        (
          ~initialRoute,
          ~routes,
          ~renderTabBar=?,
          ~safeAreaViewBackgroundColor: option(string)=?,
          ~indicatorColor: option(string)=?,
          children,
        ) => {
      ...component,
      initialState: () => {
        screens:
          routes
          |> Array.map(route =>
               {
                 route,
                 label: "",
                 labelColor: None,
                 activeLabelColor: None,
                 iconSource: None,
                 activeIconSource: None,
               }
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
        | SetOptions(
            {
              label,
              labelColor,
              activeLabelColor,
              iconSource,
              activeIconSource,
            },
            index,
          ) =>
          let screens = Js.Array.copy(state.screens);
          screens[index] = {
            ...screens[index],
            label,
            labelColor,
            activeLabelColor,
            iconSource,
            activeIconSource,
          };
          ReasonReact.Update({...state, screens});
        },
      render: self =>
        <SafeAreaView
          style=(
            Styles.tabBarContainer(safeAreaViewBackgroundColor, renderTabBar)
          )>
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
                    indicatorColor,
                  },
                )
              | None =>
                <TabBar
                  tabBarProps={
                    screens: self.state.screens,
                    currentRoute: self.state.currentRoute,
                    jumpTo: route => self.send(JumpTo(route)),
                    indicatorColor,
                  }
                />
              }
            )
          </View>
        </SafeAreaView>,
    };
    module Screen = {
      let component = ReasonReact.statelessComponent("Screen");
      let make =
          (
            ~navigation,
            ~label,
            ~labelColor: option(string)=?,
            ~activeLabelColor: option(string)=?,
            ~iconSource: option(Image.imageSource)=?,
            ~activeIconSource: option(Image.imageSource)=?,
            children,
          ) => {
        ...component,
        didMount: _self => {
          navigation.setOptions({
            label,
            labelColor,
            activeLabelColor,
            iconSource,
            activeIconSource,
          });
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