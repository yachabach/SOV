#pragma once

#include "sovLoopFunctions.h"

//**************Variable declarations

extern stateFunc currentStateFunction;
extern stateTransition transitions[];
extern systemState currentState;

//************Function declarations

systemState getSystemState(event, systemState);
systemState eventHandler(systemState, Motor &);
