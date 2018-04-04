module CreateStackNavigator:
  (Config: ReRouteTypes.NavigationConfig) =>
  {
    module StackNavigator: {
      type state;
      type options;
      type action;
      type navigation = {
        push: Config.route => unit,
        setOptions: options => unit,
        pop: unit => unit
      };
      let component:
        ReasonReact.componentSpec(
          state,
          ReasonReact.stateless,
          ReasonReact.noRetainedProps,
          ReasonReact.noRetainedProps,
          action
        );
      let make:
        (
          ~initialRoute: Config.route,
          (~currentRoute: Config.route, ~navigation: navigation) =>
          ReasonReact.reactElement
        ) =>
        ReasonReact.componentSpec(
          state,
          state,
          ReasonReact.noRetainedProps,
          ReasonReact.noRetainedProps,
          action
        );
      module Screen: {
        let component:
          ReasonReact.componentSpec(
            ReasonReact.stateless,
            ReasonReact.stateless,
            ReasonReact.noRetainedProps,
            ReasonReact.noRetainedProps,
            ReasonReact.actionless
          );
        let make:
          (
            ~navigation: navigation,
            ~style: BsReactNative.Style.t=?,
            ~headerTitle: string=?,
            ~animation: Animation.t=?,
            unit => ReasonReact.reactElement
          ) =>
          ReasonReact.componentSpec(
            ReasonReact.stateless,
            ReasonReact.stateless,
            ReasonReact.noRetainedProps,
            ReasonReact.noRetainedProps,
            ReasonReact.actionless
          );
      };
    };
  };