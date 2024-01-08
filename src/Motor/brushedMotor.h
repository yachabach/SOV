#pragma once

#include "motor.h"

class BrushedMotor : public Motor
{

public:
    BrushedMotor(direction motorDir, byte currentSpeed, byte desiredSpeed, unsigned long trvlLimit);
    BrushedMotor(direction motorDir, byte desiredSpeed, unsigned long trvlLimit);
    ~BrushedMotor();

    void setDirection(direction) override;

    void setTravelLimit(unsigned long);

    byte accelerate(void) override;
    byte decelerate(void) override;
    byte driftUpTo(byte) override;
    byte driftDownTo(byte) override;

    void start() override;
    void start(byte) override;
    void stop() override;
};
