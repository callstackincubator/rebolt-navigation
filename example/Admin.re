open Rebolt;

type action =
  | Increment;

type state = {counter: int};

let component = ReasonReact.reducerComponent("Admin");

module Styles = {
  open Style;
  let container =
    style([flex(1.), justifyContent(Center), alignItems(Center)]);
  let button = color =>
    style([
      flex(1.),
      justifyContent(Center),
      paddingHorizontal(Pt(20.)),
      maxHeight(Pt(40.)),
      marginTop(Pt(16.)),
      backgroundColor(String(color)),
      borderRadius(20.),
      width(Pt(120.)),
    ]);
  let buttonText = style([textAlign(Center)]);
  let title = style([fontSize(Float(20.))]);
};

let getHeaderTitle = counter => "Admin" ++ string_of_int(counter);

let renderButtons = (nav: NavigationConfig.StackNavigator.navigation, send) =>
  <View>
    <TouchableOpacity
      style=(Styles.button("#4cd964"))
      onPress=(_e => nav.push(NavigationConfig.Config.Home))>
      <Text style=Styles.buttonText> (ReasonReact.string("Push")) </Text>
    </TouchableOpacity>
    <TouchableOpacity
      style=(Styles.button("#ff9500")) onPress=(_e => nav.pop())>
      <Text style=Styles.buttonText> (ReasonReact.string("Pop")) </Text>
    </TouchableOpacity>
    <TouchableOpacity
      style=(Styles.button("rgb(63,97,165)"))
      onPress=(_e => send(Increment))>
      <Text style=Styles.buttonText>
        (ReasonReact.string("Change header title"))
      </Text>
    </TouchableOpacity>
  </View>;

let make = (~navigation, _children) => {
  ...component,
  initialState: () => {counter: 0},
  reducer: (action, state) =>
    switch (action) {
    | Increment => ReasonReact.Update({counter: state.counter + 1})
    },
  render: self =>
    <NavigationConfig.StackNavigator.Screen
      headerTitle=(getHeaderTitle(self.state.counter))
      navigation
      headerStyle=Style.(style([backgroundColor(String("#FFF"))]))>
      ...(
           () =>
             <View style=Styles.container>
               <Text style=Styles.title>
                 (ReasonReact.string("Admin screen"))
               </Text>
               (renderButtons(navigation, self.send))
             </View>
         )
    </NavigationConfig.StackNavigator.Screen>,
};