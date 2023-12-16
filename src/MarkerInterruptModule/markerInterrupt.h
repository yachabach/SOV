#pragma once

#include <arduino.h>
#include "./InterruptTimerModule/systemTimers.h"

const byte MARKER_PIN = 3;
const int MARKER_DEBOUNCE = 200; // required for wokwi button (ms)
const int STALE_DETECT = 1000;   // time since detect must be < 1sec

void markerDetect(void);

extern volatile unsigned long markerDetectTime;

bool home(void);

void setMarkerInterrupt(void);
