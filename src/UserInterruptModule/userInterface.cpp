#include "userInterface.h"

void checkUserInput()
{
    if (Serial.available())
    {
        String userInput = Serial.readStringUntil('\n');
        Serial.println("Detected: " + userInput + "; length: " + userInput.length());
        Serial.println("Comparison: " + String(userInput.equals("pw")));
        if (userInput.equals(String("pw")))
        {
            Serial.println("PW detected");
        }
        else
            Serial.println("Nothing recognized: " + userInput);
    }
}