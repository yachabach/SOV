#ifndef STATE_MACHINE__H
#define STATE_MACHINE__H

#include "sovLoopFunctions.h"

//**************Variable declarations

extern stateFunc currentStateFunction;
extern stateTransition transitions[];
extern systemState currentState;

//************Function declarations

systemState getSystemState(event, systemState);
systemState eventHandler(systemState, Motor &);

#endif // STATE_MACHINE_H
