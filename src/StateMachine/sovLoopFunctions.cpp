#include "sovLoopFunctions.h"

IntervalManager *ti = IntervalManager::getInstance();

int speedAdjust = ti->makeInterval(TimeInterval(driftTimeConstant));
int travelLimit = 0;
int pauseLimit = 0;
bool homeTrigger;

systemState startUp(Motor &motor, systemState sys)
{
    Serial.println("Running Startup...");
    return {.lastEvent = sys.lastEvent,
            .currentState = sys.endState,
            .endState = sys.endState};
};

systemState cruise(Motor &motor, systemState sys)
{
    Serial.println("In cruise setup...");
    motor.setDesiredSpeed(CRUISE_SPEED);
    homeTrigger = false;
    Serial.println("Motor travel limit: " + String(motor.travelLimit()));
    if (!travelLimit)
        travelLimit = ti->makeInterval({motor.travelLimit(), false});
    motor.setReverse();

    return {.lastEvent = TRANSITION_COMPLETE,
            .currentState = sys.endState,
            .endState = sys.endState};
}

systemState step_cruise(Motor &motor, systemState sys)
{
    Serial.println("In step_cruise setup...");
    homeTrigger = false;
    motor.setDesiredSpeed(FULL_SPEED);
    motor.setCurrentSpeed(FULL_SPEED);
    travelLimit = ti->makeInterval({motor.travelLimit(), true});
    pauseLimit = ti->makeInterval({1000, true});

    motor.start();

    return {.lastEvent = TRANSITION_COMPLETE,
            .currentState = sys.endState,
            .endState = sys.endState};
}

systemState accelerate(Motor &motor, systemState sys)
{
    if (ti->intervalExpired(speedAdjust))
    {
        Serial.println("In accelerate...adjusting speed");
        if (motor.accelerate() == motor.getDesiredSpeed())
        {
            return {.lastEvent = TRANSITION_COMPLETE,
                    .currentState = sys.endState,
                    .endState = sys.endState};
        }
    }
    return {.lastEvent = NO_EVENT,
            .currentState = sys.currentState,
            .endState = sys.endState};
}

systemState run(Motor &motor, systemState sys)
{
    if (!homeTrigger)
    {
        if (home())
        {
            Serial.println("Marker detected - resetting start time");
            homeTrigger = true;
            ti->getInterval(travelLimit).startTime = millis();
            return {.lastEvent = AT_HOME,
                    .currentState = sys.endState,
                    .endState = sys.endState};
        }
    }
    else
    {
        Serial.println("Travel Limit: " + String(ti->getInterval(travelLimit).interval));
        if (ti->intervalExpired(travelLimit))
        {
            homeTrigger = false;
            int travelSecs = ti->getInterval(travelLimit).startTime;
            Serial.println("Travel seconds: " + String(travelSecs));
            ti->getInterval(travelLimit).startTime = 0;

            return {.lastEvent = LIMIT_REACHED,
                    .currentState = sys.endState,
                    .endState = sys.endState};
        }
    }

    return {.lastEvent = NO_EVENT,
            .currentState = sys.currentState,
            .endState = sys.endState};
}

systemState decelerate(Motor &motor, systemState sys)
{
    if (ti->intervalExpired(speedAdjust))
    {
        if (motor.decelerate() == 0)
        {
            return {.lastEvent = TRANSITION_COMPLETE,
                    .currentState = sys.endState,
                    .endState = sys.endState};
        }
    }
    return {.lastEvent = NO_EVENT,
            .currentState = sys.currentState,
            .endState = sys.endState};
}

systemState step_run(Motor &motor, systemState sys)
{

    if (ti->intervalExpired(travelLimit))
    {
        motor.stop();
        ti->getInterval(travelLimit).startTime = 0;
        return {.lastEvent = LIMIT_REACHED,
                .currentState = sys.endState,
                .endState = sys.endState};
    }

    return {.lastEvent = NO_EVENT,
            .currentState = sys.currentState,
            .endState = sys.endState};
}

systemState pause(Motor &motor, systemState sys)
{

    if (ti->intervalExpired(pauseLimit))
    {
        motor.start();
        return {.lastEvent = LIMIT_REACHED,
                .currentState = sys.endState,
                .endState = sys.endState};
    }

    return {.lastEvent = NO_EVENT,
            .currentState = sys.currentState,
            .endState = sys.endState};
}

systemState reverseMotor(Motor &motor, systemState sys)
{
    if (!pauseLimit)
        pauseLimit = ti->makeInterval(pauseConst);
    motor.setReverse();
    if (ti->intervalExpired(pauseLimit))
    {
        return {
            .lastEvent = TRANSITION_COMPLETE,
            .currentState = sys.endState,
            .endState = sys.endState};
    }
    return {.lastEvent = NO_EVENT,
            .currentState = sys.currentState,
            .endState = sys.endState};
};

systemState seek_home(Motor &motor, systemState sys)
{
    motor.setDesiredSpeed(FULL_SPEED);
    motor.setReverse();

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
