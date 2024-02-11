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

void IntervalManager::updateInterval(int i, TimeInterval t)
{
    intervalList[i] = t;
    Serial.println("Updated interval " + String(i) + " to: " + String(intervalList[i].interval) + "ms");
}

TimeInterval &IntervalManager::getInterval(int idx)
{
    return intervalList[idx];
}

bool IntervalManager::intervalExpired(int intervalIndex)
{
    TimeInterval &interval = getInterval(intervalIndex);

    // Check for disabled timer
    if (!interval.interval)
        return true;

    unsigned long diff = millis() - interval.startTime;

    // Reset timer only if expired and autoReset is true
    if (diff >= interval.interval)
    {
        interval.startTime = interval.autoReset ? millis() : 0;
        return true;
    }
    return false;
}

void IntervalManager::resetInterval(int i)
{
    TimeInterval &interval = getInterval(i);
    interval.startTime = millis();
}

unsigned long IntervalManager::elapsedTime(unsigned long start, unsigned long end)
{
    return end - start;
}

unsigned long IntervalManager::elapsedTime(unsigned long start)
{
    return millis() - start;
}
