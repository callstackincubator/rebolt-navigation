module CreateStackNavigator:
  (Config: {type route;}) =>
  {
    module StackNavigator: {
      module Persistence: {
        let encode: array(Config.route) => Js.Json.t;
        let decode: Js.Json.t => array(Config.route);
      };
      type state;
      type options;
      type action;
      type persistedState = array(Config.route);
      type headerMode;
      type navigation = {
        push: Config.route => unit,
        setOptions: options => unit,
        pop: unit => unit,
      };
      let make:
        (
          ~initialState: persistedState,
          ~onStateChange: persistedState => unit=?,
          ~headerComponent: (~headerProps: Header.props, array('a)) =>
                            ReasonReact.component(
                              ReasonReact.stateless,
                              ReasonReact.noRetainedProps,
                              ReasonReact.actionless,
                            )
                              =?,
          ~headerMode: headerMode=?,
          (~currentRoute: Config.route, ~navigation: navigation) =>
          ReasonReact.reactElement
        ) =>
        ReasonReact.componentSpec(
          state,
          state,
          ReasonReact.noRetainedProps,
          ReasonReact.noRetainedProps,
          action,
        );
      module Animation = Animation;
      module Screen: {
        let make:
          (
            ~navigation: navigation,
            ~style: BsReactNative.Style.t=?,
            ~headerTitle: [
                            | `render(unit => ReasonReact.reactElement)
                            | `string(string)
                          ]
                            =?,
            ~headerStyle: BsReactNative.Style.t=?,
            ~headerLeft: [
                           | `render(
                               (unit => unit) => ReasonReact.reactElement,
                             )
                           | `string(string)
                         ]
                           =?,
            ~headerRight: [ | `render(unit => ReasonReact.reactElement)]=?,
            ~animation: Animation.t=?,
            unit => ReasonReact.reactElement
          ) =>
          ReasonReact.componentSpec(
            ReasonReact.stateless,
            ReasonReact.stateless,
            ReasonReact.noRetainedProps,
            ReasonReact.noRetainedProps,
            ReasonReact.actionless,
          );
      };
    };
  };