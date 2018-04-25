open Navigation;

open BsReactNative;

module Styles = {
  open Style;
  let container =
    style([flex(1.), alignItems(Center), justifyContent(Center)]);
};

let component = ReasonReact.statelessComponent("Likes");

let make = (~navigation, _children) => {
  ...component,
  render: _self =>
    <TabNavigator.Screen
      label="Likes"
      iconSource=(
        URI(
          Image.(
            imageURISource(
              ~uri="https://png.icons8.com/ios/1600/star.png",
              (),
            )
          ),
        )
      )
      activeIconSource=(
        URI(
          Image.(
            imageURISource(
              ~uri="https://png.icons8.com/ios/288/christmas-star-filled.png",
              (),
            )
          ),
        )
      )
      navigation>
      ...(
           () =>
             <View style=Styles.container>
               <Text style=Style.(style([fontSize(Float(24.))]))>
                 (ReasonReact.stringToElement("Likes"))
               </Text>
             </View>
         )
    </TabNavigator.Screen>,
};