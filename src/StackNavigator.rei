type handedOffState('state, 'action);

type screenSpec('state, 'action) = {
  initialState: unit => 'state,
  key: string,
  reducer: ('state, 'action) => 'state,
  render: ('state, 'action => unit) => ReasonReact.reactElement,
  renderChild: ('state, 'action => unit) => option(opaqueScreen),
  popChild: 'state => 'state,
  handedOffState: handedOffState('state, 'action)
}
and opaqueScreen =
  | Screen(screenSpec('state, 'action)): opaqueScreen;

type opaqueInstance;

type state;

type unknownState;

type unknownAction;

let makeScreen: unit => screenSpec(unknownState, unknownAction);

let make:
  (~initialScreen: screenSpec('a, 'b), unit) =>
  ReasonReact.componentSpec(
    opaqueInstance,
    opaqueInstance,
    ReasonReact.noRetainedProps,
    ReasonReact.noRetainedProps,
    opaqueInstance
  );
