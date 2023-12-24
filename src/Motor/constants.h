// Motor Constants

#pragma once

#include <Arduino.h>

// Motor speed control
const int driftTimeConstant = 250; // ms
const int pauseConst = 500;        // ms
const byte driftStep = 100;        // pwm units

// PWM Pin definitions
const int cwPin = 5;  // L293D pin 2
const int ccwPin = 6; // L293D pin 7