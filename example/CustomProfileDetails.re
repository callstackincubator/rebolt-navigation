open Rebolt;

open NavigationConfig;

open TabNavigator;

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

let component = ReasonReact.statelessComponent("CustomProfileDetails");

let make = (~navigation, _children) => {
  ...component,
  render: _self =>
    <Screen
      navigation
      tabItem=(
        ({isActive}) =>
          <TabBar.Item label="Details" style=(Styles.tabBarItem(isActive)) />
      )>
      ...(
           () =>
             <ScrollView>
               <View style=Styles.container>
                 <View style=Styles.titleContainer>
                   <Text style=Styles.boldText>
                     (ReasonReact.string("Contact info"))
                   </Text>
                 </View>
                 <View style=Styles.contentContainer>
                   <Text style=Styles.boldText>
                     (ReasonReact.string("Address:"))
                   </Text>
                   <Text> (ReasonReact.string("9283 Park Lane")) </Text>
                   <Text> (ReasonReact.string("I7 5SH, Chester")) </Text>
                   <Text style=Styles.boldTextWithMargin>
                     (ReasonReact.string("Phone number:"))
                   </Text>
                   <Text> (ReasonReact.string("017687 11359")) </Text>
                   <Text style=Styles.boldTextWithMargin>
                     (ReasonReact.string("Email:"))
                   </Text>
                   <Text> (ReasonReact.string("j.chow@gmail.com")) </Text>
                 </View>
               </View>
             </ScrollView>
         )
    </Screen>,
};