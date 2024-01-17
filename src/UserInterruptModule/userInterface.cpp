#include "userInterface.h"

unsigned long lastDc = 0;
int lastSpeed = 0;

void setupUserInterface()
{
    Serial.begin(9600);
    Serial.setTimeout(2000);
    pinMode(SPEED_PIN, INPUT);
    pinMode(DC_PIN, INPUT);
}

void checkUserInput(Motor &motor)
{
    if (Serial.available())
    {
        Serial.println("User input available...");
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

    // Check for a new speed
    int newSpeed = analogRead(SPEED_PIN) / 4;
    if (newSpeed != lastSpeed)
    {
        Serial.println("Detected speed change - setting speed");
        lastSpeed = newSpeed;
        motor.setMotorSpeed(newSpeed * motor.getMotorDir());
    }

    // Check for a new Duty Cycle
    unsigned long sv = analogRead(DC_PIN);
    if (sv != lastDc)
    {
        lastDc = sv;
        int newDutyCycle = (sv * 100) / 1023;
        motor.setDutyCycle(newDutyCycle);
        Serial.println("Updated dutycyle to: " + String(newDutyCycle));
    }
}