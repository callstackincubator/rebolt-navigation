type commonNavigation('route, 'options) = {
  push: 'route => unit,
  replace: 'route => unit,
  setOptions: 'options => unit,
  pop: unit => unit,
};
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
      type navigation = commonNavigation(Config.route, options);
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
            ~style: Rebolt.Style.t=?,
            ~headerTitle: string=?,
            ~headerStyle: Rebolt.Style.t=?,
            ~headerLeft: Header.returnsComponent=?,
            ~headerCenter: Header.returnsComponent=?,
            ~headerRight: Header.returnsComponent=?,
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
