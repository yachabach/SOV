#ifndef INTERRUPT_TIMER_H
#define INTERRUPT_TIMER_H

#include <Arduino.h>

int startInterruptTimer(int hz, byte outPin = 0);

extern volatile unsigned long appClock;
extern volatile byte signal2Hz;
extern int appClockFreq;

#endif // INTERRUPT_TIMER_H