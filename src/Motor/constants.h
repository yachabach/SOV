// Motor Parent Types and Constants
#pragma once

#include <Arduino.h>

// Motor speed control***************
const byte SPEED_PIN = A0;
const byte DC_PIN = A1;

// Time stopped before reverse starts
const int PAUSE_CONST = 500; // ms.

// Possible Directions - ^3 toggles between the two
enum direction
{
    CW = 1,
    CCW = -1
};
