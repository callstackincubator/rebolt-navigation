open BsReactNative;

open Utils;

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
  | Screen(screenSpec('state, 'action)): opaqueScreen
and handedOffState('state, 'action) = ref(option(screenSpec('state, 'action)));

type instance('state, 'action) = {
  screen: screenSpec('state, 'action),
  instanceState: 'state,
  child: option(opaqueInstance),
  header: Header.config,
  animatedValue: Animated.Value.t,
  animation: Animation.t
}
and opaqueInstance =
  | Instance(instance('state, 'action)): opaqueInstance;

let rec updateInstance =
        (
          Instance(
            {screen, instanceState: currentState, child: oldChild} as currentInstance
          ),
          send
        ) =>
  Instance(
    {
      let thisState = currentState;
      {
        ...currentInstance,
        screen,
        instanceState: thisState,
        child: {
          let newChild =
            screen.renderChild(
              thisState,
              action => {
                let nextState = screen.reducer(thisState, action);
                send(
                  Instance({
                    ...currentInstance,
                    screen,
                    instanceState: nextState,
                    child: oldChild
                  })
                );
              }
            );
          switch (oldChild, newChild) {
          | (Some(_), None)
          | (None, None) => None
          | (
              Some(
                Instance(
                  {screen: oldScreen, instanceState: oldState, child: oldChild} as oldChildImpl
                )
              ),
              Some(Screen(childScreen))
            ) =>
            childScreen.handedOffState := Some(childScreen);
            switch oldScreen.handedOffState^ {
            | Some(newChildScreen) =>
              childScreen.handedOffState := None;
              Some(
                updateInstance(
                  Instance({
                    ...oldChildImpl,
                    screen: newChildScreen,
                    instanceState: oldState,
                    child: oldChild
                  }),
                  childUpdate =>
                  send(
                    Instance({
                      ...oldChildImpl,
                      screen: newChildScreen,
                      instanceState: oldState,
                      child: Some(childUpdate)
                    })
                  )
                )
              );
            | None =>
              childScreen.handedOffState := None;
              Some(renderNewChild(childScreen, send, screen, thisState));
            };
          | (None, Some(Screen(childScreen))) =>
            Some(renderNewChild(childScreen, send, screen, thisState))
          };
        }
      };
    }
  )
and renderNewChild:
  'childState 'childAction 'state 'action .
  (
    screenSpec('childState, 'childAction),
    opaqueInstance => unit,
    screenSpec('state, 'action),
    'state
  ) =>
  opaqueInstance
 =
  (childScreen, send, screen, thisState) => {
    let header = Header.default;
    let animation = Animation.default;
    let animatedValue = Animated.Value.create(1.0);
    updateInstance(
      Instance({
        screen: childScreen,
        instanceState: childScreen.initialState(),
        child: None,
        header,
        animation,
        animatedValue
      }),
      childUpdate =>
      send(
        Instance({
          screen,
          instanceState: thisState,
          child: Some(childUpdate),
          header,
          animation,
          animatedValue
        })
      )
    );
  };

module Styles = {
  open Style;
  let fill =
    style([
      position(Absolute),
      top(Pt(0.0)),
      left(Pt(0.0)),
      right(Pt(0.0)),
      bottom(Pt(0.0))
    ]);
  let flex = style([flex(1.0)]);
  let card =
    style([
      backgroundColor(String("#E9E9EF")),
      shadowColor(String("black")),
      shadowOffset(~width=0.0, ~height=0.0),
      shadowOpacity(0.2),
      shadowRadius(5.0)
    ]);
  let stackContainer = concat([flex, style([flexDirection(ColumnReverse)])]);
};

let headerAnimatedValue = Animated.Value.create(0.0);

/**
 * Gestures
 */
module Gestures = {
  /** PanGestureHandler from `react-native-gesture-handler */
  module PanHandler = {
    [@bs.module "react-native-gesture-handler"]
    external view : ReasonReact.reactClass = "PanGestureHandler";
    let make =
        (
          ~onGestureEvent,
          ~maxDeltaX,
          ~enabled,
          ~onHandlerStateChange,
          ~minDeltaX,
          ~hitSlop,
          children
        ) =>
      ReasonReact.wrapJsForReason(
        ~reactClass=view,
        ~props={
          "onGestureEvent": onGestureEvent,
          "onHandlerStateChange": onHandlerStateChange,
          "maxDeltaX": maxDeltaX,
          "minDeltaX": minDeltaX,
          "enabled": Js.Boolean.to_js_boolean(enabled),
          "hitSlop": hitSlop
        },
        children
      );
  };
  let screenWidth = Dimensions.get(`window)##width;
  /** Raw value as updated via `handler` from PanGestureHandler */
  let animatedValue = Animated.Value.create(0.0);
  let handler =
    Animated.event(
      [|{
          "nativeEvent": {
            "translationX": animatedValue
          }
        }|],
      {"useNativeDriver": true}
    );
  /** Interpolated progress in range of 0 to 1 (start to end) */
  let animatedProgress =
    AnimatedUtils.interpolate(
      animatedValue,
      ~inputRange=[0.0, float_of_int(screenWidth)],
      ~outputRange=`float([0.0, 1.0]),
      ~extrapolate=Animated.Interpolation.Clamp,
      ()
    );
  /** Interpolated progress in range of 0 to 1 (start to end) */
  let animatedProgress =
    AnimatedUtils.interpolate(
      animatedValue,
      ~inputRange=[0.0, float_of_int(screenWidth)],
      ~outputRange=`float([0.0, 1.0]),
      ~extrapolate=Animated.Interpolation.Clamp,
      ()
    );
  /**
       * Called when gesture state changes (5 - end)
       *
       * At the end of the animation, make sure to reset gesture
       * state to `0` and update all the other animated values
       * accordingly.
       */
  let onStateChange =
      (
        event,
        activeScreen,
        previousScreen,
        activeScreenIndex,
        commitViewChange
      ) => {
    let e = event##nativeEvent;
    switch e##state {
    | 5 =>
      let toValue =
        e##translationX > screenWidth / 2 || e##velocityX > 150.00 ?
          screenWidth : 0;
      Animated.CompositeAnimation.start(
        Animated.Spring.animate(
          ~value=animatedValue,
          ~velocity=e##velocityX,
          ~useNativeDriver=Js.true_,
          ~toValue=`raw(float_of_int(toValue)),
          ()
        ),
        ~callback=
          _end_ =>
            if (toValue != 0) {
              Animated.Value.setValue(previousScreen.animatedValue, 0.0);
              Animated.Value.setValue(activeScreen.animatedValue, 1.0);
              Animated.Value.setValue(
                headerAnimatedValue,
                float_of_int(activeScreenIndex)
              );
              Animated.Value.setValue(animatedValue, 0.0);
            },
        commitViewChange()
      );
    | _ => ()
    };
  };
};

let rec renderAll =
        (
          Instance({
            screen,
            instanceState,
            child,
            header,
            animatedValue,
            animation
          }),
          send,
          depth
        ) => {
  let animationStyle =
    if (depth == 0) {
      Style.style([]);
    } else {
      let screenAnimation =
        switch child {
        | Some(Instance({animation: childAnimation})) => childAnimation
        | None => animation
        };
      Animated.Value.add(Gestures.animatedProgress, animatedValue)
      |> screenAnimation.forCard({idx: depth + 1});
    };
  [
    (
      {Header.header, animation, key: screen.key},
      ReasonReact.element(
        ~key=screen.key,
        Animated.View.make(
          ~style=Style.(concat([Styles.fill, animationStyle])),
          [|
            ReasonReact.element(
              View.make([|
                screen.render(
                  instanceState,
                  action => {
                    let nextState = screen.reducer(instanceState, action);
                    send(
                      Instance({
                        screen,
                        instanceState: nextState,
                        child,
                        header,
                        animatedValue,
                        animation
                      })
                    );
                  }
                )
              |])
            )
          |]
        )
      )
    ),
    ...switch child {
       | Some(childInstance) =>
         renderAll(
           childInstance,
           childUpdate =>
             send(
               Instance({
                 screen,
                 instanceState,
                 child: Some(childUpdate),
                 header,
                 animatedValue,
                 animation
               })
             ),
           depth + 1
         )
       | None => []
       }
  ];
};

type updateAnimation =
  | Push(opaqueInstance, opaqueInstance, int)
  | Pop(opaqueInstance, opaqueInstance, int)
  | Replace;

type state =
  | Displaying(opaqueInstance)
  | Animating(updateAnimation, opaqueInstance);

let container = ReasonReact.reducerComponent("Navigator_Container");

let make = (~initialScreen, ()) => {
  ...container,
  initialState: () =>
    updateInstance(
      Instance({
        header: Header.default,
        animation: Animation.default,
        animatedValue: Animated.Value.create(1.0),
        screen: initialScreen,
        instanceState: initialScreen.initialState(),
        child: None
      }),
      (_) =>
      ()
    ),
  reducer: (newInstance, _) => ReasonReact.Update(newInstance),
  didMount: ({send, state}) => {
    let rec sender = screenUpdate =>
      send(updateInstance(screenUpdate, sender));
    ReasonReact.Update(updateInstance(state, sender));
  }
};

let performAnimation =
    (~first, ~firstToValue, ~secondToValue, ~second, ~secondIndex, ~finished) =>
  Animated.CompositeAnimation.start(
    Animated.parallel(
      [|
        second.animation.func(
          ~value=Gestures.animatedValue,
          ~toValue=`raw(0.0)
        ),
        second.animation.func(
          ~value=headerAnimatedValue,
          ~toValue=`raw(float_of_int(secondIndex))
        ),
        second.animation.func(
          ~value=first.animatedValue,
          ~toValue=`raw(firstToValue)
        ),
        second.animation.func(
          ~value=second.animatedValue,
          ~toValue=`raw(secondToValue)
        )
      |],
      {
        module J = {
          external unsafe_expr :
            (~stopTogether: 'a0) => {. "stopTogether": 'a0} =
            ""
            "BS:2.2.2\132\149¦¾\000\000\000\020\000\000\000\005\000\000\000\016\000\000\000\014\145  B ,stopTogether@@";
        };
        J.unsafe_expr(~stopTogether=Js.Boolean.to_js_boolean(false));
      }
    ),
    ~callback=
      end_ =>
        if (Js.to_bool(end_##finished)) {
          finished();
        },
    ()
  );

let onDidUpdate = (updateType, finished) =>
  switch updateType {
  | Replace => ()
  | Push(Instance(fromInstance), Instance(toInstance), toIndex) =>
    performAnimation(
      ~first=fromInstance,
      ~firstToValue=-1.0,
      ~second=toInstance,
      ~secondToValue=0.0,
      ~secondIndex=toIndex,
      ~finished
    )
  | Pop(Instance(fromInstance), Instance(toInstance), toIndex) =>
    performAnimation(
      ~first=fromInstance,
      ~firstToValue=0.0,
      ~second=toInstance,
      ~secondToValue=1.0,
      ~secondIndex=toIndex,
      ~finished
    )
  };

let renderImplementation = (state, send) => {
  let rec sender = screenUpdate => send(updateInstance(screenUpdate, sender));
  let screens =
    switch state {
    | Animating(Pop(fromInstance, _, _), instance) =>
      List.append(
        renderAll(instance, sender, 0),
        renderAll(fromInstance, (_) => (), 0)
      )
      |> Array.of_list
    | Displaying(instance)
    | Animating(_, instance) => renderAll(instance, sender, 0) |> Array.of_list
    };
  let screenWidth = Dimensions.get(`window)##width;
  /**
 * Aquapoint is the distance between parent and its sibling
 * used by default on iOS (auto-layout constraint). This is
 * the used for defining how far from the screen your gesture
 * can start.
 *
 * Source: https://goo.gl/FVKnzZ
 */
  let aquaPoint = 20;
  ReasonReact.element(
    View.make(
      ~style=Styles.stackContainer,
      [|
        ReasonReact.element(
          Gestures.PanHandler.make(
            ~minDeltaX=aquaPoint,
            ~hitSlop={"right": aquaPoint - screenWidth},
            ~maxDeltaX=screenWidth,
            ~enabled=Array.length(screens) > 1,
            ~onGestureEvent=Gestures.handler,
            ~onHandlerStateChange=(_) => Gestures.onStateChange,
            [|
              ReasonReact.element(
                Animated.View.make(
                  ~style=Styles.flex,
                  [|screens |> Array.map(snd) |> ReasonReact.arrayToElement|]
                )
              )
            |]
          )
        ),
        ReasonReact.element(
          Header.PlatformHeader.make(
            ~animatedValue=
              Animated.Value.add(
                headerAnimatedValue,
                Animated.Value.multiply(
                  Gestures.animatedProgress,
                  Animated.Value.create(-1.0)
                )
              ),
            ~pop=(_) => (),
            ~activeScreen=Array.length(screens) - 1,
            ~screens=screens |> Array.map(fst),
            [||]
          )
        )
      |]
    )
  );
};

type unknownState = unit;

type unknownAction = unit;

let makeScreen = () => {
  handedOffState: ref(None),
  initialState: () => (),
  reducer: (_, _) => (),
  render: (_, _) => ReasonReact.nullElement,
  renderChild: (_, _) => None,
  popChild: () => (),
  key: ""
};
