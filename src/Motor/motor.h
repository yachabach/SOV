// Motor Parent Class Header File
#pragma once

#include "constants.h" //Already includes Arduino.h
#include "./definitions/states.h"
#include "./InterruptTimerModule/systemTimers.h"

class Motor
{
private:
    direction motorDir;
    int motorSpeed;
    unsigned long trvlLimit;

    bool travelLimitFlag = false;

    virtual void setTimersAndIntervals() = 0;
    virtual void setControllerDirection() = 0;

public:
    Motor(
        direction motorDir = CW,
        byte motorSpeed = 0,
        unsigned long trvlLimit = 0);
    ~Motor();

    IntervalManager *ti;

    void setMotorDir(direction);
    direction getMotorDir(void);

    void setMotorSpeed(int);
    int getMotorSpeed();

    void setTrvlLimit(unsigned long);
    unsigned long getTrvlLimit(void);

    virtual void start() = 0;
    virtual void run() = 0;
    virtual void stop() = 0;
    virtual void resetTravelMon() = 0;
    virtual void setDutyCycle(int) = 0;

    void reverse();
    void start(int); // Probably don't have to override

    bool atTravelLimit();
    void setTravelLimitFlag(bool);
};
