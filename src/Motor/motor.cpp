#include "motor.h"

Motor::Motor(direction dir, byte speed, byte desSpeed, unsigned long limit)
    : motorDir(dir), currentSpeed(speed), desiredSpeed(desSpeed), trvlLimit(limit){
                                                                      // pinMode(cwPin, OUTPUT);
                                                                      // pinMode(ccwPin, OUTPUT);
                                                                  };

Motor::Motor(direction dir, byte desSpeed, unsigned long limit)
    : motorDir(dir), currentSpeed(0), desiredSpeed(desSpeed), trvlLimit(limit){
                                                                  // pinMode(cwPin, OUTPUT);
                                                                  // pinMode(ccwPin, OUTPUT);
                                                              };

Motor::~Motor(){};

void Motor::setMotorDir(direction newDirection) { motorDir = newDirection; };
direction Motor::getMotorDir(void) { return motorDir; };

void Motor::setCurrentSpeed(byte newSpeed) { currentSpeed = newSpeed; }
byte Motor::getCurrentSpeed() { return currentSpeed; }

void Motor::setDesiredSpeed(byte newSpeed) { desiredSpeed = newSpeed; }
byte Motor::getDesiredSpeed() { return desiredSpeed; }

void Motor::setTrvlLimit(unsigned long newLimit) { trvlLimit = newLimit; };
unsigned long Motor::getTrvlLimit() { return trvlLimit; };

byte Motor::accelerate() { return 0; }
byte Motor::decelerate() { return 0; }
byte Motor::driftUpTo(byte) { return 0; }
byte Motor::driftDownTo(byte) { return 0; }

void Motor::start() {}
void Motor::start(byte speed) {}
void Motor::stop() {}

direction Motor::setReverse()
{
    direction newDir = motorDir == CW ? CCW : CW;
    setMotorDir(newDir);
    return newDir;
}