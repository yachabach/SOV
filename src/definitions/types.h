//*********Type Declarations
#pragma once

#include "events.h"
#include "states.h"
#include "./Motor/motor.h"

struct systemState
{
    event lastEvent;
    state currentState;
    state endState;
};

// Pointer to the currently looping function
using stateFunc = systemState (*)(Motor &, systemState);

// Object to define a reaction to an event
struct stateTransition
{
    event triggerEvent;
    state presentState;
    stateFunc stateFunction;
    state endState;
};