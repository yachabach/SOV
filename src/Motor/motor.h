// Motor Header File

#pragma once

// #include <arduino.h>
#include "constants.h"

// Possible Directions - ^3 toggles between the two
enum direction
{
    CW = cwPin,
    CCW = ccwPin
};

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

    void setDirection(direction);
    direction travelDirection(void) const;

    void setTravelLimit(unsigned long);
    unsigned long travelLimit(void) const;

    void setCurrentSpeed(byte);
    byte getCurrentSpeed(void);
    void setDesiredSpeed(byte);
    byte getDesiredSpeed(void);
    byte accelerate(void);
    byte decelerate(void);
    byte driftUpTo(byte);
    byte driftDownTo(byte);

    void start();
    void start(byte);

    void stop();

    direction setReverse(void);
};
