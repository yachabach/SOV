#include "systemTimers.h"

void setupTimers(IntervalManager *intervalManager)
{
    intervalManager->makeInterval({});
}

IntervalManager *IntervalManager::instance = nullptr;

IntervalManager::IntervalManager()
{
    listSize = 0;
}

IntervalManager *IntervalManager::getInstance()
{
    return instance ? instance : new IntervalManager();
}

IntervalManager::~IntervalManager()
{
}

int IntervalManager::makeInterval(TimeInterval newInterval)
{
    if (listSize < 10)
    {
        intervalList[listSize] = newInterval;
        listSize++;
        return listSize - 1;
    }
    return -1;
}

TimeInterval &IntervalManager::getInterval(int idx)
{
    return intervalList[idx];
}

bool IntervalManager::intervalExpired(int intervalIndex)
{
    TimeInterval &interval = getInterval(intervalIndex);
    if (interval.startTime == 0 && interval.autoReset)
        interval.startTime = millis();
    else if ((millis() - interval.startTime >= interval.interval) && (interval.startTime != 0))
    {
        interval.startTime = millis();
        return true;
    }

    return false;
}

unsigned long IntervalManager::elapsedTime(unsigned long start, unsigned long end)
{
    Serial.println("Elapsed Time: " + String(end - start));
    return end - start;
}

unsigned long IntervalManager::elapsedTime(unsigned long start)
{
    return millis() - start;
}
