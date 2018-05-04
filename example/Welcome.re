open NavigationConfig;

open BsReactNative;

let screenWidth = Dimensions.get(`screen)##width;

module Style = {
  open Style;
  let container =
    style([flex(1.), alignItems(Center), justifyContent(Center)]);
  let button = color =>
    style([
      marginVertical(Pt(5.)),
      justifyContent(Center),
      alignItems(Center),
      backgroundColor(String(color)),
      width(Pt(float_of_int(screenWidth / 2))),
      borderRadius(25.),
      paddingVertical(Pt(10.)),
    ]);
  let text =
    style([
      color(String("#f2f2f2")),
      fontWeight(`_600),
      fontSize(Float(20.)),
    ]);
};

let component = ReasonReact.statelessComponent("Welcome");

type examples =
  | Tab
  | TabCustom
  | Stack;

let examplesList = [|Tab, TabCustom, Stack|];

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
                        | Tab => "Tab navigation"
                        | Stack => "Stack"
                        | TabCustom => "Custom TabBar"
                        };
                      <TouchableOpacity
                        key=route
                        style=(Style.button("#5ac8fa"))
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
                          (ReasonReact.string(route))
                        </Text>
                      </TouchableOpacity>;
                    })
                 |> ReasonReact.array
               )
             </View>
         )
    </StackNavigator.Screen>,
};