// Spirit Of Victory (SOV) Loop Function Header
#pragma once

#include "./Motor/motor.h"
#include "./InterruptTimerModule/systemTimers.h"
#include "./MarkerInterruptModule/markerInterrupt.h"
#include "./definitions/systemDefinitions.h"

extern int travelLimit;

// loop functions
systemState startUp(Motor &, systemState);
systemState cruise(Motor &, systemState);
systemState pause(Motor &, systemState);
systemState run(Motor &, systemState);
systemState stop(Motor &, systemState);
systemState reverse(Motor &, systemState);
systemState full_speed(Motor &);
systemState seek_home(Motor &, systemState);
systemState idle(Motor &, systemState);
