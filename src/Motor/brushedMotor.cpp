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
    setDutyCycle(runDutyCycle);
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

unsigned long BrushedMotor::calculateDutyInterval(int dc)
{
    Serial.println("Calculating dc interval with: " + String(dc));
    if (dc <= MAX_ON_DUTY && dc != 0)
        return dc * (cycleDuration / 100);
    else
    {
        Serial.println("Returning cycleDuration: " + String(cycleDuration));
        return cycleDuration;
    }
}

void BrushedMotor::setDutyCycle(int dc)
{
    runDutyCycle = dc;
    onDutyTime = calculateDutyInterval(runDutyCycle);
    offDutyTime = cycleDuration - onDutyTime;
    Serial.println("updated duty cycle - onDutyTime: " + String(onDutyTime));
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
    onDuty = onDutyTime != 0;
    Serial.println("Cycle start - On duty time: " + String(onDutyTime));
    ti->updateInterval(dutyTimer, TimeInterval(onDutyTime, millis(), false));
    if (onDuty)
    {
        int pwm = (255 * getMotorSpeed()) / 100;
        Serial.println("Writing speed and direction: Current Speed: " + String(getMotorSpeed()));
        analogWrite(dirPin, pwm);
    }
}

void BrushedMotor::run()
{
    setTravelLimitFlag(ti->intervalExpired(travelIntervalTimer));

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
