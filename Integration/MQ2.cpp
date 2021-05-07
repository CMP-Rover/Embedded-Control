#include "MQ2.h"
#include "Arduino.h"

MQ2::MQ2(int analog, int digital, int warmup)
    : analogPin(analog), digitalPin(digital), WarmupPeroid(warmup) {}

MQ2::~MQ2() {}

int MQ2::GetGasConcentration()
{
    int reading = analogRead(analogPin);
    // Remaps the read value to the sensor to a concentration (check the datasheet)
  
    return map(reading, analogVmin, analogVmax, MIN_PPM, MAX_PPM); 
}

bool MQ2::IsGasDetected()
{
    pinMode(digitalPin, INPUT);
    return digitalRead(digitalPin);
}

void MQ2::PrintMQ2Data(int data,bool detected)
{
    
    int gasConc = GetGasConcentration();
    data=gasConc;
    Serial.print("Sensor Value: ");
    Serial.print(gasConc);
    detected=IsGasDetected();
    if (detected)
    {
        Serial.print(" | Gas detected!");
    }

    Serial.println("");
}

void MQ2::Warmup()
{
    delay(WarmupPeroid);
}
