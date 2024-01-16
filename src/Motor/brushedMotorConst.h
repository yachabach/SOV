#pragma once

// PWM Pin definitions
const int cwPin = 5;  // Arduino:5->L293D:2
const int ccwPin = 6; // Arduino:6->L293D:7

// Minimum intermittent times for brushed motor
const byte MIN_DUTY_TIME = 25;       // ms. Min time for motor to run
const int MIN_CYCLE_DURATION = 2500; // ms. Min time on + off
const int MAX_ON_DUTY = 30;          // Max on-duty percent (int)