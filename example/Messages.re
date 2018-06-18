open NavigationConfig;

open TabNavigator;

open Rebolt;

let component = ReasonReact.statelessComponent("Messages");

let itemWidth = float_of_int(Dimensions.get(`screen)##width);

module Styles = {
  open Style;
  let container = custom =>
    style([
      flex(1.),
      alignItems(Center),
      justifyContent(Center),
      marginTop(Pt(custom ? 80. : 0.)),
    ]);
  let title = style([color(String("#000")), fontSize(Float(24.))]);
  let listItem =
    style([
      flex(1.),
      flexDirection(Row),
      width(Pt(itemWidth)),
      height(Pt(35.)),
      justifyContent(SpaceBetween),
      alignItems(Center),
      paddingHorizontal(Pt(5.)),
      borderColor(String("gray")),
      borderBottomWidth(0.2),
      backgroundColor(String("white")),
    ]);
  let name = style([color(String("#323232")), fontSize(Float(15.))]);
  let rightActions =
    style([
      flexDirection(Row),
      justifyContent(SpaceBetween),
      alignItems(Center),
    ]);
  let icon = style([height(Pt(20.)), width(Pt(20.))]);
};

type contact = {
  name: string,
  count: int,
};

type data = array(contact);

let data = [|
  {name: "Davin Roth", count: 645},
  {name: "Milton Walsh", count: 12},
  {name: "Malakai Brady", count: 99},
  {name: "Xavier Obrien", count: 1},
  {name: "Ariel Gill", count: 32},
  {name: "Avery Lozano", count: 15},
  {name: "Davian Osborne", count: 7},
  {name: "Jovan Vega", count: 2},
|];

let renderItem =
  FlatList.renderItem((contact: FlatList.renderBag(contact)) =>
    <View style=Styles.listItem>
      <Text style=Styles.name> (ReasonReact.string(contact.item.name)) </Text>
      <View style=Styles.rightActions>
        <Text>
          (ReasonReact.string(string_of_int(contact.item.count)))
        </Text>
        <TouchableOpacity>
          <Image
            style=Styles.icon
            source=(Required(Packager.require("./assets/right.png")))
          />
        </TouchableOpacity>
      </View>
    </View>
  );

let extractor = (item, _index) => item.name;

let make = (~navigation, ~custom: bool, _children) => {
  ...component,
  render: _self =>
    <Screen
      tabItem=(
        ({isActive}) =>
          <TabBar.Item
            label="Messages"
            style=(
              Style.style([Style.color(String(isActive ? "blue" : "gray"))])
            )
          />
      )
      navigation>
      ...(
           () =>
             <View style=(Styles.container(custom))>
               <FlatList data renderItem keyExtractor=extractor />
             </View>
         )
    </Screen>,
};