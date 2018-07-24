open Rebolt;

module Styles = {
  open Style;
  let tabBarItem = isActive =>
    style([
      color(isActive ? String("#fff") : String("#eee")),
      fontSize(Float(16.)),
    ]);
  let container =
    style([
      backgroundColor(String("white")),
      margin(Pt(16.)),
      marginBottom(Pt(56.)),
      borderRadius(6.),
      width(Pt(float_of_int(Dimensions.get(`window)##width - 32))),
    ]);
  let titleContainer =
    style([
      backgroundColor(String("#eee")),
      borderRadius(6.),
      padding(Pt(16.)),
    ]);
  let contentContainer =
    style([backgroundColor(String("#fff")), padding(Pt(16.))]);
  let boldText = style([fontWeight(`Bold)]);
  let boldTextWithMargin = style([fontWeight(`Bold), marginTop(Pt(8.))]);
};

let component = ReasonReact.statelessComponent("CustomProfileStats");

let make = (~navigation, _children) => {
  ...component,
  render: _self =>
    <NavigationConfig.TabNavigator.Screen
      navigation
      tabItem=(
        ({isActive}) =>
          <NavigationConfig.TabNavigator.TabBar.Item
            label="Stats"
            style=(Styles.tabBarItem(isActive))
          />
      )>
      ...(
           () =>
             <ScrollView>
               <View style=Styles.container>
                 <View style=Styles.titleContainer>
                   <Text style=Styles.boldText>
                     (ReasonReact.string("Statistics"))
                   </Text>
                 </View>
                 <View style=Styles.contentContainer>
                   <Text style=Styles.boldText>
                     (ReasonReact.string("Steps:"))
                   </Text>
                   <Text> (ReasonReact.string("9830")) </Text>
                   <Text style=Styles.boldTextWithMargin>
                     (ReasonReact.string("Distance:"))
                   </Text>
                   <Text> (ReasonReact.string("7.44km")) </Text>
                 </View>
               </View>
             </ScrollView>
         )
    </NavigationConfig.TabNavigator.Screen>,
};