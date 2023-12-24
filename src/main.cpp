#include <Arduino.h>
// #include "InterruptTimerModule/interrupt-timer.h"
#include "UserInterruptModule/userInterrupt.h"
// #include "MarkerInterruptModule/markerInterrupt.h"
#include "StateMachine/stateMachine.h"
#include "StateDisplay/stateDisplay.h"
// #include "Motor/motor.h"
// #include "./InterruptTimerModule/systemTimers.h"

#define TICK_LED 13

Motor sovMotor(CW, 100, 10);
systemState currentState = {POWER_UP, START_UP, STOPPED};

void setup()
{
  Serial.begin(9600);
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

  // put your main code here, to run repeatedly:
}
