open BsReactNative;

module Styles = {
  open Style;
  type textSize =
    | Small
    | Regular;
  let tabContainer = style([flex(1.)]);
  let screenContainer =
    style([
      position(Absolute),
      top(Pt(0.)),
      right(Pt(0.)),
      bottom(Pt(0.)),
      left(Pt(0.)),
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
  let tabBar =
    switch (Platform.os()) {
    | Platform.Android =>
      style([
        flexDirection(Row),
        backgroundColor(String("#fff")),
        height(Pt(48.)),
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
  let tabBarItemText = (~textSize) =>
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
        color(String("#2180f7")),
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
        color(String("#2180f7")),
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
    module TabBar = {
      module Item = {
        let component = ReasonReact.statelessComponent("TabBarItem");
        let make =
            (
              ~label,
              ~icon: option(Image.imageSource)=?,
              ~style: option(Style.t)=?,
              _children,
            ) => {
          ...component,
          render: _self =>
            switch (label, icon) {
            | (label, Some(icon)) =>
              <View style=Styles.tabBarItem>
                <Image source=icon style=Styles.tabBarItemIcon />
                (
                  switch (label) {
                  | "" => ReasonReact.null
                  | _ =>
                    let itemText =
                      switch (Platform.os()) {
                      | Platform.Android => String.uppercase(label)
                      | _ => label
                      };
                    <Text
                      style=(
                        Style.concat([
                          Styles.tabBarItemText(~textSize=Small),
                          switch (style) {
                          | Some(style) => style
                          | None => Style.style([])
                          },
                        ])
                      )>
                      (ReasonReact.string(itemText))
                    </Text>;
                  }
                )
              </View>
            | (label, None) =>
              switch (label) {
              | "" => ReasonReact.null
              | _ =>
                let itemText =
                  switch (Platform.os()) {
                  | Platform.Android => String.uppercase(label)
                  | _ => label
                  };
                <Text
                  style=(
                    Style.concat([
                      Styles.tabBarItemText(~textSize=Regular),
                      switch (style) {
                      | Some(style) => style
                      | None => Style.style([])
                      },
                    ])
                  )>
                  (ReasonReact.string(itemText))
                </Text>;
              }
            },
        };
      };
      let component = ReasonReact.statelessComponent("TabBar");
      let make = (~tabBarProps: tabBarProps, _children) => {
        ...component,
        render: _self =>
          <View style=Styles.tabBar>
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
                       ReasonReact.null;
                   })
                |> ReasonReact.array
              | _ => ReasonReact.null
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
                       (screen.tabItem({isActive: isActive}))
                     </View>
                   </TouchableWithoutFeedback>;
                 })
              |> ReasonReact.array
            )
          </View>,
      };
    };
    /* TODO: find index of initialRoute */
    let activeScreenAnimatedValue = Animated.Value.create(float_of_int(1));
    module Gestures = {
      let screenWidth = Dimensions.get(`window)##width;
      let animatedValue = Animated.Value.create(0.0);
      let handler =
        Animated.event(
          [|{
              "nativeEvent": {
                "translationX": animatedValue,
              },
            }|],
          {"useNativeDriver": true},
        );
      /** Interpolated progress in range of 0 to 1 (start to end) */
      let animatedProgress =
        AnimatedUtils.interpolate(
          animatedValue,
          ~inputRange=[0.0, float_of_int(screenWidth)],
          ~outputRange=`float([0.0, 1.0]),
          ~extrapolate=Animated.Interpolation.Clamp,
          (),
        );
      let onStateChange = (event, _self) => {
        let _e = event##nativeEvent;
        ();
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
               {route, tabItem: _tabItemProps => ReasonReact.null}
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
        | SetOptions({tabItem}, index) =>
          let screens = Js.Array.copy(state.screens);
          screens[index] = {...screens[index], tabItem};
          ReasonReact.Update({...state, screens});
        },
      render: self => {
        let screenWidth = Dimensions.get(`window)##width;
        let aquaPoint = 20;
        let animatedValue =
          Animated.Value.add(
            activeScreenAnimatedValue,
            Animated.Value.multiply(
              Gestures.animatedProgress,
              Animated.Value.create(-1.0),
            ),
          );
        let size = Array.length(routes);
        <SafeAreaView
          style=(
            Styles.tabBarContainer(safeAreaViewBackgroundColor, renderTabBar)
          )>
          <View style=Style.(style([flex(1.)]))>
            <GestureHandlers.PanHandler
              minDeltaX=aquaPoint
              hitSlop={"right": 0}
              maxDeltaX=screenWidth
              enabled=(size > 1)
              onGestureEvent=Gestures.handler
              onHandlerStateChange=(self.handle(Gestures.onStateChange))>
              <Animated.View style=Styles.tabContainer>
                (
                  self.state.screens
                  |> Array.mapi((index, screen) => {
                       let isActive = self.state.currentRoute === screen.route;
                       let screenAnimatedValue =
                         Animated.Value.add(
                           Animated.Value.create(float_of_int(index)),
                           Animated.Value.multiply(
                             animatedValue,
                             Animated.Value.create(-1.),
                           ),
                         );
                       <Animated.View
                         key=(string_of_int(index))
                         style=(
                           Style.concat([
                             Styles.screenContainer,
                             screenAnimatedValue
                             |> TabInterpolator.default.forCard,
                           ])
                         )
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
                       </Animated.View>;
                     })
                  |> ReasonReact.array
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
              </Animated.View>
            </GestureHandlers.PanHandler>
          </View>
        </SafeAreaView>;
      },
    };
    module Screen = {
      let component = ReasonReact.statelessComponent("Screen");
      let make =
          (
            ~navigation,
            ~tabItem: tabItemProps => ReasonReact.reactElement,
            children,
          ) => {
        ...component,
        didMount: _self => {
          navigation.setOptions({tabItem: tabItem});
          ();
        },
        render: _self => <View style=Styles.tabContainer> (children()) </View>,
      };
    };
  };
};