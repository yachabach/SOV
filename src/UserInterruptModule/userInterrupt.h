// UserInterruptModule Header File

#pragma once

#include <Arduino.h>
#include "constants.h"
#include "./InterruptTimerModule/systemTimers.h"
#include "./definitions/events.h"

extern volatile unsigned long lastButtonEvent; // for debounce
extern volatile unsigned long buttonPressTime;
extern volatile unsigned long buttonReleaseTime;

extern unsigned long lastShortPushTime;

void setupButtonInterrupt(void);

void buttonReleasedInterrupt(void);

void buttonPushedInterrupt(void);

event buttonStatus(void);
