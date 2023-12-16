#include "timeFunctions.h"

float timeDiff(unsigned long time1, unsigned long time2)
{
    return float(time1 - time2) / appClockFreq;
}