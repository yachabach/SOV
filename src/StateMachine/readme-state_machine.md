# Arduino State Machine

This state machine allows separation of concerns and aviods the use of switch statements.  With the latest event, it compares context and chooses a function that will be run with each loop of the arduino controller.  beginStateFunc and endStateFunc are boolean values that can be used by the state function if they require startup and/or shutdown functionality.

## Events

State Machine requires that events are defined in an application-specific event enum type.  For example, the Spirit of Victory (SOV) project had the following definition in SOV.h:

```
typedef enum event {
  NO_EVENT,
  LONG_USER_PUSH,		  // >2 sec
  SHORT_USER_PUSH,		// <1 sec
  MARKER_DETECT,
  START_UP
};
```

## States

It also requires a state enum type.  SOV.h contained these states:

```
typedef enum state {
  STOPPED,
  CRUISING,
  CALIBRATING,
  ANY
};
```
