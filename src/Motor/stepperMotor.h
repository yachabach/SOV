#pragma once

#include "motor.h"
#include "stepperMotorConst.h"
// #include "./InterruptTimerModule/systemTimers.h"

class StepperMotor : public Motor
{
private:
    int intervalRange;
    int stepIntervalTimer;

    unsigned int stepsTraveled = 0;

    void setOutputPins();
    void setTimersAndIntervals();
    void setControllerDirection() override;
    int getStepInterval();

public:
    StepperMotor(direction motorDir, int motorSpeed, unsigned long trvlLimit);
    ~StepperMotor();

    void setTravelLimit(unsigned long);
    void resetTravelMon() override;

    void start() override;
    void run() override;
    void stop() override;

    void setDutyCycle(int);
};
