#include "./StateMachine/stateMachine.h"
#include "./InterruptTimerModule/interrupt-timer.h"

const int statusPin = 4;

void setupDisplay(void);
void displayState(systemState);