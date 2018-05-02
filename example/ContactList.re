open NavigationConfig;

open TabNavigator;

open BsReactNative;

let component = ReasonReact.statelessComponent("Contacts");

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
  let online = online =>
    style([
      height(Pt(10.)),
      width(Pt(10.)),
      backgroundColor(String(online ? "#4cd964" : "#ff3b3a")),
      borderRadius(20.),
      marginHorizontal(Pt(7.)),
    ]);
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
  online: bool,
};

type data = array(contact);

let data = [|
  {name: "John Doe", online: true},
  {name: "Marry Jane", online: false},
  {name: "Mario Speedwagon", online: true},
  {name: "Petey Cruiser", online: false},
  {name: "Anna Sthesia", online: true},
  {name: "Paul Molive", online: true},
  {name: "Anna Mull", online: false},
  {name: "Gail Forcewind", online: false},
  {name: "Paige Turner", online: false},
  {name: "Bob Frapples", online: false},
  {name: "Walter Melon", online: true},
  {name: "Nick R. Bocker", online: true},
  {name: "Barb Ackue", online: true},
  {name: "Buck Kinnear", online: true},
  {name: "Greta Life", online: false},
  {name: "Ira Membrit", online: false},
  {name: "Shonda Leer", online: false},
  {name: "Brock Lee", online: false},
  {name: "Maya Didas", online: false},
  {name: "Rick O'Shea", online: false},
  {name: "Pete Sariya", online: false},
  {name: "Monty Carlo", online: false},
|];

let renderItem = (nav: StackNavigator.navigation) =>
  FlatList.renderItem((contact: FlatList.renderBag(contact)) =>
    <TouchableOpacity
      style=Styles.listItem onPress=(_e => nav.push(Config.UserProfile))>
      <Text style=Styles.name>
        (ReasonReact.stringToElement(contact.item.name))
      </Text>
      <View style=Styles.rightActions>
        <View style=(Styles.online(contact.item.online)) />
        <TouchableOpacity>
          <Image
            style=Styles.icon
            source=(
              Required(Packager.require("../../../example/assets/right.png"))
            )
          />
        </TouchableOpacity>
      </View>
    </TouchableOpacity>
  );

let extractor = (item, _index) => item.name;

let make =
    (
      ~navigation,
      ~stackNavigation: StackNavigator.navigation,
      ~custom: bool,
      _children,
    ) => {
  ...component,
  render: _self =>
    <Screen
      tabItem=(
        ({isActive}) =>
          <TabBar.Item
            label="Contacts"
            style=(
              Style.style([Style.color(String(isActive ? "blue" : "gray"))])
            )
          />
      )
      navigation>
      ...(
           () =>
             <View style=(Styles.container(custom))>
               <FlatList
                 data
                 renderItem=(renderItem(stackNavigation))
                 keyExtractor=extractor
               />
             </View>
         )
    </Screen>,
};