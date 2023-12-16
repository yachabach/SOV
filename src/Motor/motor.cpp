#include "motor.h"

Motor::Motor(direction dir, byte speed, byte desSpeed, unsigned long limit) : motorDir(dir), currentSpeed(speed), desiredSpeed(desSpeed), trvlLimit(limit)
{
    pinMode(cwPin, OUTPUT);
    pinMode(ccwPin, OUTPUT);
};

Motor::Motor(direction dir, byte desSpeed, unsigned long limit) : motorDir(dir), currentSpeed(0), desiredSpeed(desSpeed), trvlLimit(limit)
{
    pinMode(cwPin, OUTPUT);
    pinMode(ccwPin, OUTPUT);
};

Motor::~Motor(){};

void Motor::setDirection(direction newDir)
{
    motorDir = newDir;
    analogWrite(motorDir ^ 3, 0);
}
direction Motor::travelDirection() const { return motorDir; }

void Motor::setCurrentSpeed(byte newSpeed) { currentSpeed = newSpeed; }
byte Motor::getCurrentSpeed() { return currentSpeed; }
void Motor::setDesiredSpeed(byte newSpeed) { desiredSpeed = newSpeed; }
byte Motor::getDesiredSpeed() { return desiredSpeed; }
byte Motor::accelerate() { return driftUpTo(desiredSpeed); }
byte Motor::decelerate() { return driftDownTo(0); }

byte Motor::driftUpTo(byte limitSpeed)
{
    currentSpeed = (currentSpeed + driftStep >= limitSpeed) ? limitSpeed : currentSpeed + driftStep;
    Serial.println("Motor is drifting up to: " + String(currentSpeed));
    start();
    return currentSpeed;
}

byte Motor::driftDownTo(byte limitSpeed)
{
    currentSpeed = (currentSpeed - driftStep <= limitSpeed) ? limitSpeed : currentSpeed - driftStep;
    Serial.println("Motor is drifting down to: " + String(currentSpeed));
    start();
    return currentSpeed;
}

direction Motor::setReverse()
{
    direction newDir = motorDir == CW ? CCW : CW;
    setDirection(newDir);
    return newDir;
}

void Motor::setTravelLimit(unsigned long newLimit) { trvlLimit = newLimit >= 0 ? newLimit : 0; }
unsigned long Motor::travelLimit() const { return trvlLimit; }

void Motor::start()
{
    int pwm = int(255 * float(currentSpeed / 100.0));
    Serial.print("Writing speed and direction: ");
    Serial.println(pwm);
    analogWrite(motorDir, pwm);
}

void Motor::start(byte speed)
{
    setCurrentSpeed(speed);
    start();
}

// Causes motor to stop but does not change programmed speed
void Motor::stop()
{
    Serial.println("Motor stopping...");
    analogWrite(motorDir, 0);
}
