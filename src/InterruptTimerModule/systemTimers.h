#pragma once

#include "interrupt-timer.h"

struct TimeInterval
{
    unsigned long interval;
    unsigned long startTime;
    bool autoReset;

    TimeInterval()
        : interval(0), startTime(0), autoReset(true) {}
    TimeInterval(unsigned long i)
        : interval(i), startTime(0), autoReset(true) {}
    TimeInterval(unsigned long i, bool b)
        : interval(i), startTime(0), autoReset(b) {}
    TimeInterval(unsigned long i, unsigned long s, bool b)
        : interval(i), startTime(s), autoReset(b) {}
};

class IntervalManager
{
private:
    IntervalManager();
    static IntervalManager *instance; // Singleton instance

    TimeInterval intervalList[10];
    byte listSize;

public:
    static IntervalManager *getInstance(void);
    ~IntervalManager();
    TimeInterval &getInterval(int);
    int makeInterval(TimeInterval);
    void updateInterval(int, TimeInterval);
    void resetInterval(int);
    bool intervalExpired(int);
    unsigned long elapsedTime(unsigned long, unsigned long);
    unsigned long elapsedTime(unsigned long);
};

extern IntervalManager intervalManager;
