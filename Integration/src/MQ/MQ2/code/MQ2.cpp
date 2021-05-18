#include "MQ2.h"
#include "Arduino.h"
#include "../../../Util/Util.h"

MQ2::MQ2(int analog, int digital, int warmup)
    : analogPin(analog), digitalPin(digital), WarmupPeroid(warmup) {}

MQ2::~MQ2() {}

// The MQ2's voltage-PPM curve is linear
float MQ2::GetGasConcentration()
{
    int reading = analogRead(analogPin);  
    return mapfloat(reading, analogVmin, analogVmax, MIN_PPM_MQ2, MAX_PPM_MQ2); 
}

bool MQ2::IsGasDetected()
{
    pinMode(digitalPin, INPUT);
    return digitalRead(digitalPin);
}

void MQ2::PrintMQ2Data()
{
    String output = "MQ2: PPM: ";
    float gasConc = GetGasConcentration();
    output += String(gasConc, 2);
    if (IsGasDetected())
    {
        output += " | Gas detected!";
    }
    Serial.println(output);
}

void MQ2::Warmup()
{
    delay(WarmupPeroid);
}
