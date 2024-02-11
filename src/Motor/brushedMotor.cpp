#include "brushedMotor.h"

BrushedMotor::BrushedMotor(
    direction dir,
    int speed,
    unsigned long limit) : Motor(dir, speed, limit)
{
    setPWMPins();
    setTimersAndIntervals();
}

BrushedMotor::~BrushedMotor() {}

void BrushedMotor::setPWMPins()
{
    pinMode(cwPin, OUTPUT);
    pinMode(ccwPin, OUTPUT);
};

void BrushedMotor::setTimersAndIntervals()
{
    travelIntervalTimer = ti->makeInterval(TimeInterval(getTrvlLimit(), false));
    cycleDuration = MIN_CYCLE_DURATION;
    dutyTimer = ti->makeInterval(TimeInterval({0, false}));
}

void BrushedMotor::setControllerDirection()
{
    dirPin = (getMotorDir() == CW) ? cwPin : ccwPin;
    byte lowPin = (dirPin == cwPin) ? ccwPin : cwPin;
    digitalWrite(lowPin, 0);
}

void BrushedMotor::setTravelLimit(unsigned long newLimit)
{
    setTrvlLimit((newLimit >= 0) ? newLimit : 0);
    ti->updateInterval(travelIntervalTimer, TimeInterval(getTrvlLimit()));
}

void BrushedMotor::resetTravelMon()
{
    setTravelLimitFlag(false);
    ti->resetInterval(travelIntervalTimer);
}

void BrushedMotor::start()
{
    resetTravelMon();
    setControllerDirection();
}

void BrushedMotor::run()
{
    setTravelLimitFlag(ti->intervalExpired(travelIntervalTimer));
    int pwm = (255 * getMotorSpeed() * getMotorDir()) / 100;
    analogWrite(dirPin, pwm);
}

// Stop function for duty cycle
void BrushedMotor::dcStop()
{
    Serial.println("Motor dc-stopping...offDutyTime: " + String(offDutyTime));
    onDuty = false;
    ti->updateInterval(dutyTimer, TimeInterval(offDutyTime, millis(), false));
    stop();
}

void BrushedMotor::stop()
{
    analogWrite(dirPin, 0);
}
