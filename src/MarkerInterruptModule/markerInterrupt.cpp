#include "markerInterrupt.h"

volatile unsigned long markerDetectTime = 0;
volatile unsigned long lastDetect = 0;

unsigned long lastDetectTime = 0;

IntervalManager *markerTi = IntervalManager::getInstance();

bool home()
{
    bool result = markerTi->elapsedTime(markerDetectTime) < STALE_DETECT;
    markerDetectTime = 0;
    return result;
}

void markerDetect()
{
    unsigned long timeNow = millis();
    if (timeNow - lastDetect > MARKER_DEBOUNCE)
    {
        lastDetect = markerDetectTime = timeNow;
        Serial.println("Marker detected");
    }
};

void setMarkerInterrupt()
{
    pinMode(MARKER_PIN, INPUT);
    digitalWrite(MARKER_PIN, LOW); // Protect against noise
    attachInterrupt(
        digitalPinToInterrupt(MARKER_PIN),
        markerDetect,
        RISING);
}
