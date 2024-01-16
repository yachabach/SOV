#pragma once

// Directional Control Pin
const int dirCtlPin = 5;
const int stepSignalPin = 6;

// Tutorial suggests steppers can respond down to 700 microseconds
const int MIN_STEP_INTERVAL = 1;    // ms.  Fastest allowable speed.
const int MAX_STEP_INTERVAL = 2000; // ms.  Slowest allowable speed.