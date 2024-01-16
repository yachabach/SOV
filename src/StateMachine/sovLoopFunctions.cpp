#include "sovLoopFunctions.h"

IntervalManager *ti = IntervalManager::getInstance();

int pauseLimit = ti->makeInterval(TimeInterval(PAUSE_CONST, false));

systemState startUp(Motor &motor, systemState sys)
{
    return {sys.lastEvent, sys.endState, sys.endState};
};

systemState cruise(Motor &motor, systemState sys)
{
    motor.setMotorSpeed(FULL_SPEED);
    motor.start();

    return {.lastEvent = TRANSITION_COMPLETE,
            .currentState = sys.endState,
            .endState = sys.endState};
}

systemState run(Motor &motor, systemState sys)
{
    systemState newState = sys;
    newState.lastEvent = NO_EVENT;

    if (home())
    {
        Serial.println("Marker detected - resetting start time");
        motor.resetTravelMon();
        newState.lastEvent = AT_HOME;
        newState.currentState = sys.endState;
    }

    motor.run();

    if (motor.atTravelLimit())
    {
        Serial.println("Found travel limit.");
        motor.setTravelLimitFlag(false);
        newState.lastEvent = LIMIT_REACHED;
        newState.currentState = sys.endState;
    }

    return newState;
}

systemState stop(Motor &motor, systemState sys)
{
    motor.stop();
    ti->resetInterval(pauseLimit);

    return {
        .lastEvent = TRANSITION_COMPLETE,
        .currentState = sys.endState,
        .endState = sys.endState};
}

systemState pause(Motor &motor, systemState sys)
{
    systemState newState = sys;
    newState.lastEvent = NO_EVENT;

    if (ti->intervalExpired(pauseLimit))
    {
        newState.lastEvent = LIMIT_REACHED;
        newState.currentState = sys.endState;
    }

    return newState;
}

systemState reverse(Motor &motor, systemState sys)
{
    motor.reverse();

    return {.lastEvent = TRANSITION_COMPLETE,
            .currentState = sys.endState,
            .endState = sys.endState};
};

systemState seek_home(Motor &motor, systemState sys)
{
    motor.setMotorSpeed(FULL_SPEED);
    motor.reverse();

    return {.lastEvent = TRANSITION_COMPLETE,
            .currentState = sys.endState,
            .endState = sys.endState};
};

systemState idle(Motor &motor, systemState sys)
{
    return {.lastEvent = NO_EVENT,
            .currentState = sys.endState,
            .endState = sys.endState};
};
