#include "stateDisplay.h"

void setupDisplay()
{
    pinMode(statusPin, OUTPUT);
}

void displayState(systemState state)
{
    byte signal = state.currentState == LOST ? HIGH : state.currentState == SEEKING_HOME ? signal2Hz
                                                                                         : LOW;
    digitalWrite(statusPin, signal);
}