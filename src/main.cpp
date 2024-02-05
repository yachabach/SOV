#include <Arduino.h>
#include "UserInterruptModule/userInterrupt.h"
#include "StateMachine/stateMachine.h"
#include "StateDisplay/stateDisplay.h"
#include "Motor/brushedMotor.h"
#include "./UserInterruptModule/userInterface.h"

#define TICK_LED 13

BrushedMotor sovMotor(CW, 100, 30000);
systemState currentState = {POWER_UP, START_UP, STOPPED};

void setup()
{
  setupUserInterface();
  appClockFreq = startInterruptTimer(10, statusPin);
  setupButtonInterrupt();
  setMarkerInterrupt();
  setupDisplay();
  Serial.println("Starting SOV main...");
  currentState = eventHandler(currentState, sovMotor);
}

void loop()
{
  currentState = eventHandler(
      getSystemState(buttonStatus(), currentState), sovMotor);

  displayState(currentState);
  checkUserInput(sovMotor);
}
