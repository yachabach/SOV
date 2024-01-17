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
    dutyTimer = ti->makeInterval(TimeInterval({0, false}));
    cycleDuration = MIN_CYCLE_DURATION;
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

void BrushedMotor::setDutyCycle(int dc)
{
    if (dc <= MAX_ON_DUTY && dc != 0)
    {
        runDutyCycle = dc;
        onDutyTime = runDutyCycle * (cycleDuration / 100);
        Serial.println("calculating onDutyTime - " + String(onDutyTime));
        offDutyTime = cycleDuration - onDutyTime;
    }
    else
    {
        runDutyCycle = 100;
        onDutyTime = offDutyTime = 0; // disables interval timer
    }
    ti->updateInterval(dutyTimer, TimeInterval(onDutyTime));
}

int BrushedMotor::getDutyCycle() { return runDutyCycle; }

void BrushedMotor::start()
{
    resetTravelMon();
    setControllerDirection();
    cycleStart();
}

void BrushedMotor::cycleStart()
{
    onDuty = true;
    Serial.println("Cycle start - On duty time: " + String(onDutyTime));
    ti->updateInterval(dutyTimer, TimeInterval(onDutyTime, millis(), false));
}

void BrushedMotor::run()
{
    setTravelLimitFlag(ti->intervalExpired(travelIntervalTimer));
    if (onDuty)
    {
        int pwm = (255 * getMotorSpeed()) / 100;
        Serial.println("Writing speed and direction: Current Speed: " + String(getMotorSpeed()));
        analogWrite(dirPin, pwm);
    }
    if (ti->intervalExpired(dutyTimer))
    {
        Serial.println("Handling duty cycle..." + String(getDutyCycle()));
        onDuty ? dcStop() : cycleStart();
    }
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
