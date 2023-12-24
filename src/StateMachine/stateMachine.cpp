#include "stateMachine.h"

stateFunc currentStateFunction = startUp;

systemState getSystemState(event userEvent, systemState sys)
{
  return {
      .lastEvent = (userEvent == NO_EVENT) ? sys.lastEvent : userEvent,
      .currentState = sys.currentState,
      .endState = sys.endState};
}

// Array of event reactions
stateTransition transitions[]{
    // Cruise transitions
    // {SHORT_USER_PUSH, STOPPED, cruise, RESUMING},
    // {TRANSITION_COMPLETE, RESUMING, accelerate, CRUISING},
    // {TRANSITION_COMPLETE, CRUISING, run, CRUISING},
    // {AT_HOME, CRUISING, run, REVERSING},
    // {LIMIT_REACHED, REVERSING, decelerate, PAUSED},
    // {TRANSITION_COMPLETE, PAUSED, reverseMotor, RESUMING},

    {SHORT_USER_PUSH, STOPPED, step_cruise, CRUISING},
    {TRANSITION_COMPLETE, CRUISING, step_run, CRUISING},
    {LIMIT_REACHED, CRUISING, pause, PAUSED},
    {LIMIT_REACHED, PAUSED, step_run, CRUISING},

    // Cruise Error
    {LIMIT_REACHED, CRUISING, decelerate, LOST},
    {TRANSITION_COMPLETE, LOST, idle, STOPPED},

    // Stop Logic
    {SHORT_USER_PUSH, ANY, decelerate, STOPPED},
    {TRANSITION_COMPLETE, STOPPED, idle, STOPPED},

    // Seek Home Transitions
    {LONG_USER_PUSH, STOPPED, seek_home, SEEKING_HOME},
    {TRANSITION_COMPLETE, SEEKING_HOME, accelerate, RUNNING_HOME},
    {TRANSITION_COMPLETE, RUNNING_HOME, run, SEEKING_HOME},
    {AT_HOME, SEEKING_HOME, decelerate, STOPPED},

    // Startup Logic
    {POWER_UP, START_UP, startUp, STOPPED},
    {POWER_UP, STOPPED, idle, STOPPED},
};

stateTransition *findTransition(event e, state s)
{
  for (byte i = 0; i < sizeof(transitions) / sizeof(stateTransition); i++)
  {
    if (transitions[i].triggerEvent == e && (transitions[i].presentState == s || transitions[i].presentState == ANY))
      return &transitions[i];
  };
  return nullptr;
}

systemState eventHandler(systemState sysState, Motor &motor)
{
  systemState newState = sysState;
  stateTransition *trans = nullptr;
  if (newState.lastEvent != NO_EVENT)
  {
    Serial.println("Getting new event: " + String(newState.lastEvent) + "; current state: " + String(newState.currentState));
    trans = findTransition(newState.lastEvent, newState.currentState);
    if (trans)
    {
      newState.endState = trans->endState;
      currentStateFunction = trans->stateFunction;
    }
    else
    {
      newState.lastEvent = NO_EVENT;
      currentStateFunction = startUp;
      return newState;
    }
  }
  newState = currentStateFunction(motor, newState);
  return newState;
};
