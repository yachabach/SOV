/*
User Interrupt sets up an interrupt vector to a debounced routine that detects a press and a release of a button.

The cruise routine will observe the difference between buttonPressTime and buttonReleaseTime and fire an event when it detects a long or short push of the button.
*/
#include "userInterrupt.h"

volatile unsigned long lastButtonEvent = 0; // for debounce
volatile unsigned long buttonPressTime = 0;
volatile unsigned long buttonReleaseTime = 0;

IntervalManager *uiTi = IntervalManager::getInstance();

void buttonReleasedInterrupt()
{
  unsigned long timeNow = millis();
  if (timeNow - lastButtonEvent > DEBOUNCE_DELAY)
  {
    lastButtonEvent = buttonReleaseTime = timeNow;
    attachInterrupt(
        digitalPinToInterrupt(PUSH_BUTTON),
        buttonPushedInterrupt,
        FALLING);
  }
}

void buttonPushedInterrupt()
{
  unsigned long timeNow = millis();
  if (timeNow - lastButtonEvent > DEBOUNCE_DELAY)
  {
    lastButtonEvent = buttonPressTime = timeNow;
    attachInterrupt(
        digitalPinToInterrupt(PUSH_BUTTON),
        buttonReleasedInterrupt,
        RISING);
  }
}

event buttonStatus()
{
  event nextEvent = NO_EVENT;
  if (buttonPressTime && (buttonReleaseTime >= buttonPressTime))
  {
    // Serial.println("In button event; buttonPressTime: " + String(buttonPressTime) + "; release: " + String(buttonReleaseTime));
    if (uiTi->elapsedTime(buttonPressTime, buttonReleaseTime) > BUTTON_PUSH_INTERVAL)
      nextEvent = LONG_USER_PUSH;
    else
    {
      buttonPressTime = 0;
      while (uiTi->elapsedTime(buttonReleaseTime) <= BUTTON_PUSH_INTERVAL && nextEvent != DOUBLE_USER_PUSH)
        nextEvent = buttonPressTime ? DOUBLE_USER_PUSH : SHORT_USER_PUSH;
    }
    buttonPressTime = buttonReleaseTime = 0; // This press was processed - reset to avoid loop until next press
  }
  return nextEvent;
}

void setupButtonInterrupt()
{
  pinMode(PUSH_BUTTON, INPUT);
  digitalWrite(PUSH_BUTTON, HIGH); // Protect against noise
  attachInterrupt(
      digitalPinToInterrupt(PUSH_BUTTON),
      buttonPushedInterrupt,
      FALLING);
}