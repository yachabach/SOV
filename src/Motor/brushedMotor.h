#pragma once

#include "motor.h"
#include "brushedMotorConst.h"

class BrushedMotor : public Motor
{
private:
    // Timers
    int travelIntervalTimer; // for travel limit
    int dutyTimer;
    unsigned long onDutyTime;  // Intermitent run time
    unsigned long offDutyTime; // Intermitent stop time
    void setTimersAndIntervals();

    // Arduino Interface
    byte dirPin; // Direction dependent
    void setControllerDirection() override;
    void setPWMPins(); // Set output pins for PWM signals

    // Intermitent run functionality
    bool onDuty = false;
    int cycleDuration;
    int runDutyCycle = 100; // 100 or < 30
    void cycleStart();
    void dcStop();
    unsigned long calculateDutyInterval(int);

public:
    BrushedMotor(
        direction motorDir = CW,
        int Speed = 0,
        unsigned long trvlLimit = 0);
    ~BrushedMotor();

    void setTravelLimit(unsigned long);
    void resetTravelMon() override;
    void setDutyCycle(int);
    int getDutyCycle();

    void start() override;
    void run() override;
    void stop() override;
};
