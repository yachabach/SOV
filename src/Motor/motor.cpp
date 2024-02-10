#include "motor.h"

Motor::Motor(
    direction dir,
    int speed,
    unsigned long limit) : motorDir(dir),
                           motorSpeed(speed),
                           trvlLimit(limit)
{
    ti = IntervalManager::getInstance();
};

Motor::~Motor(){};

void Motor::setMotorDir(direction newDirection) { motorDir = newDirection; };
direction Motor::getMotorDir(void) { return motorDir; };

void Motor::setMotorSpeed(int newSpeed) { motorSpeed = newSpeed; }
int Motor::getMotorSpeed() { return motorSpeed; }

void Motor::setTrvlLimit(unsigned long newLimit) { trvlLimit = newLimit; };
unsigned long Motor::getTrvlLimit() { return trvlLimit; };

void Motor::start(int speed)
{
    setMotorSpeed(speed);
    setMotorDir(speed < 0 ? CCW : CW);
    start();
}

void Motor::reverse() { start(getMotorSpeed() * -1); }

bool Motor::atTravelLimit() { return travelLimitFlag; }
void Motor::setTravelLimitFlag(bool b) { travelLimitFlag = b; }
