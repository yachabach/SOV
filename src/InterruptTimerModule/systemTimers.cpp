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

// Only create a new instance if one doesn't already exist
IntervalManager *IntervalManager::getInstance()
{
    return instance ? instance : new IntervalManager();
}

IntervalManager::~IntervalManager()
{
}

int IntervalManager::makeInterval(TimeInterval newInterval)
{
    // Look for an equal interval that already exists
    for (int i = 0; i < static_cast<int>(sizeof(intervalList) / sizeof(intervalList[0])); ++i)
    {
        if (intervalList[i].interval == newInterval.interval)
            return i;
    }

    // No matches? If we have room for a new one, put it at the end
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
