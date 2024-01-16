#include "stepperMotor.h"

StepperMotor::StepperMotor(direction dir, int speed, unsigned long limit)
    : Motor(dir, speed, limit)
{
    setTimersAndIntervals();
    setOutputPins();
}

StepperMotor::~StepperMotor() {}

void StepperMotor::setOutputPins()
{
    pinMode(dirCtlPin, OUTPUT);
    pinMode(stepSignalPin, OUTPUT);
};

void StepperMotor::setTimersAndIntervals()
{
    intervalRange = (MAX_STEP_INTERVAL - MIN_STEP_INTERVAL) + 1;
    stepIntervalTimer = ti->makeInterval(TimeInterval(getStepInterval()));
}

int StepperMotor::getStepInterval()
{
    /*
    - Speed is set as a % (expressed as int) of full motor speed
    - stepper cannot receive pulses faster than 1 ms.  So 1 ms return value would be 100%
    - The largest step interval defines the slowest allowable speed
    - The intervalRange between "largest" and '1' is the granularity of speed choices.
    - stepInterval = ((int)%_Desired_Speed * intervalRange)/100
    - stepInterval = (50 * 1000)/100 = 500 ms for 50% power
    */

    int si = (getMotorSpeed() * intervalRange) / 100;
    return si >= MIN_STEP_INTERVAL ? si : MIN_STEP_INTERVAL;
}

void StepperMotor::setControllerDirection()
{
    getMotorDir() == CW ? digitalWrite(dirCtlPin, 0) : digitalWrite(dirCtlPin, 1);
}

void StepperMotor::setTravelLimit(unsigned long newLimit)
{
    setTrvlLimit(newLimit >= 0 ? newLimit : 0);
}

void StepperMotor::resetTravelMon()
{
    setTravelLimitFlag(false);
    stepsTraveled = 0;
}

void StepperMotor::start()
{
    resetTravelMon();
    setControllerDirection();
    ti->updateInterval(stepIntervalTimer, getStepInterval());
    Serial.println("Writing speed and direction: Current Speed: " + String(getMotorSpeed()));
}

void StepperMotor::run()
{
    setTravelLimitFlag(stepsTraveled == getTrvlLimit());
    if (ti->intervalExpired(stepIntervalTimer))
    {
        digitalWrite(stepSignalPin, !digitalRead(stepSignalPin));
        stepsTraveled++;
    }
}

// Causes motor to stop but does not change programmed speed
void StepperMotor::stop()
{
    Serial.println("Motor stopping...");
}

void StepperMotor::setDutyCycle(int) {}
