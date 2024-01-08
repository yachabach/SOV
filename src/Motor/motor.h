// Motor Parent Class Header File
#pragma once

#include "constants.h" //Already includes Arduino.h

class Motor
{
private:
    direction motorDir;
    byte currentSpeed;
    byte desiredSpeed;
    unsigned long trvlLimit;

public:
    Motor(direction motorDir, byte currentSpeed, byte desiredSpeed, unsigned long trvlLimit);
    Motor(direction motorDir, byte desiredSpeed, unsigned long trvlLimit);
    ~Motor();

    void setMotorDir(direction);
    direction getMotorDir(void);

    void setCurrentSpeed(byte);
    byte getCurrentSpeed();

    void setDesiredSpeed(byte);
    byte getDesiredSpeed();

    void setTrvlLimit(unsigned long);
    unsigned long getTrvlLimit(void);

    virtual void setDirection(direction) = 0;

    virtual byte accelerate();
    virtual byte decelerate();
    virtual byte driftUpTo(byte);
    virtual byte driftDownTo(byte);

    virtual void start() = 0;
    virtual void start(byte) = 0;
    virtual void stop() = 0;

    direction setReverse(void);
};
