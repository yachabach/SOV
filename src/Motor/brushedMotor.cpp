#include "brushedMotor.h"

BrushedMotor::BrushedMotor(direction dir, byte speed, byte desSpeed, unsigned long limit)
    : Motor(dir, speed, desSpeed, limit)
{
    pinMode(cwPin, OUTPUT);
    pinMode(ccwPin, OUTPUT);
};

BrushedMotor::BrushedMotor(direction dir, byte desSpeed, unsigned long limit)
    : Motor(dir, desSpeed, limit)
{
    pinMode(cwPin, OUTPUT);
    pinMode(ccwPin, OUTPUT);
};

BrushedMotor::~BrushedMotor(){};

void BrushedMotor::setDirection(direction newDir)
{
    setMotorDir(newDir);
    analogWrite(getMotorDir() ^ 3, 0);
}

void BrushedMotor::setTravelLimit(unsigned long newLimit) { setTrvlLimit(newLimit >= 0 ? newLimit : 0); }

byte BrushedMotor::accelerate() { return driftUpTo(getDesiredSpeed()); }
byte BrushedMotor::decelerate() { return driftDownTo(0); }

byte BrushedMotor::driftUpTo(byte limitSpeed)
{
    setCurrentSpeed((getCurrentSpeed() + driftStep >= limitSpeed) ? limitSpeed : getCurrentSpeed() + driftStep);
    Serial.println("Motor is drifting up to: " + String(getCurrentSpeed()));
    start();
    return getCurrentSpeed();
}

byte BrushedMotor::driftDownTo(byte limitSpeed)
{
    setCurrentSpeed((getCurrentSpeed() - driftStep <= limitSpeed) ? limitSpeed : getCurrentSpeed() - driftStep);
    Serial.println("Motor is drifting down to: " + String(getCurrentSpeed()));
    start();
    return getCurrentSpeed();
}

void BrushedMotor::start()
{
    int pwm = int(255 * float(getCurrentSpeed() / 100.0));
    Serial.println("Writing speed and direction: Current Speed: " + String(getCurrentSpeed()));
    analogWrite(getMotorDir(), pwm);
}

void BrushedMotor::start(byte speed)
{
    setCurrentSpeed(speed);
    start();
}

// Causes motor to stop but does not change programmed speed
void BrushedMotor::stop()
{
    Serial.println("Motor stopping...");
    analogWrite(getMotorDir(), 0);
}
