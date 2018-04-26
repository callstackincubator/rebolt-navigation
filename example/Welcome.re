open NavigationConfig;

open TabExample;

open BsReactNative;

let screenWidth = Dimensions.get(`screen)##width;

module Style = {
  open Style;
  let container =
    style([flex(1.), alignItems(Center), justifyContent(Center)]);
  let element =
    style([
      marginVertical(Pt(5.)),
      justifyContent(Center),
      alignItems(Center),
      backgroundColor(String("#af2141")),
      height(Pt(80.)),
      width(Pt(float_of_int(screenWidth - 20))),
      borderColor(String("#474747")),
      borderWidth(2.),
      borderRadius(5.),
    ]);
  let text =
    style([
      color(String("#f2f2f2")),
      fontWeight(`_600),
      fontSize(Float(20.)),
    ]);
};

type state = {routes: array(string)};

let component = ReasonReact.statelessComponent("Welcome");

type examples =
  | Tab
  | TabCustom
  | Stack;

let examplesList = [|TabCustom, Tab, Stack|];

let make = (~navigation: StackNavigator.navigation, _children) => {
  ...component,
  render: _self =>
    <StackNavigator.Screen navigation headerTitle="Examples">
      ...(
           () =>
             <View style=Style.container>
               (
                 examplesList
                 |> Array.map(example => {
                      let route =
                        switch (example) {
                        | Tab => "Tab"
                        | Stack => "Stack"
                        | TabCustom => "Custom TabBar"
                        };
                      <TouchableOpacity
                        key=route
                        style=Style.element
                        onPress=(
                          () =>
                            switch (example) {
                            | Tab => navigation.push(Config.TabExample)
                            | Stack => navigation.push(Config.Home)
                            | TabCustom =>
                              navigation.push(Config.CustomTabBarExample)
                            }
                        )>
                        <Text style=Style.text>
                          (ReasonReact.stringToElement(route))
                        </Text>
                      </TouchableOpacity>;
                    })
                 |> ReasonReact.arrayToElement
               )
             </View>
         )
    </StackNavigator.Screen>,
};