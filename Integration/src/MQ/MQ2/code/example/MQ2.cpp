#include "MQ2.h"
#include "Arduino.h"
#include "Util.h" // Uncomment this if you're working with MQ2's example.ino (Take a copy of Util.h, Util.cpp with the ino)
//#include "../../../Util/Util.h" // Uncomment this if you're working with Integration.ino

MQ2::MQ2(int analog, int digital, int warmup, int Threshold)
    : analogPin(analog), digitalPin(digital), WarmupPeroid(warmup) {
      currentThreshold = SensitivityThresholds[Threshold];
      }

MQ2::~MQ2() {}

// The MQ2's voltage-PPM curve is linear
// If the current reading is less than the current analog threshold, returns 0;
float MQ2::GetGasConcentration(bool realConc)
{
    int reading = analogRead(analogPin);  
    if(reading < currentThreshold) reading = 0;
    
    if(realConc)
      return mapfloat(reading, analogVmin, analogVmax, MIN_PPM_MQ2, MAX_PPM_MQ2); 
    else
      return reading;
}

bool MQ2::IsGasDetected()
{
    pinMode(digitalPin, INPUT);
    return digitalRead(digitalPin);
}

void MQ2::PrintMQ2Data()
{
    String output = "MQ2: PPM: ";
    float gasConc = GetGasConcentration(false);
    output += String(gasConc, 2);
    if (IsGasDetected())
    {
        output += " | Gas detected!";
    }
//    Serial.println(output);
    Serial.println(gasConc);
}

void MQ2::Warmup()
{
    delay(WarmupPeroid);
}

void MQ2::LowSensitivity()
{
  
}
