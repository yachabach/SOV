// Motor Constants

#pragma once

#include <Arduino.h>

// Motor speed control
const int driftTimeConstant = 500; // ms
const int pauseConst = 500;        // ms
const byte driftStep = 10;         // pwm units

// PWM Pin definitions
const int cwPin = 5;
const int ccwPin = 6;