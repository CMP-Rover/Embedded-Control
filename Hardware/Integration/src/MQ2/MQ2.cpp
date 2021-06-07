#include "MQ2.h"
#include "Arduino.h"
// #include "Util.h" // Uncomment this if you're working with MQ2's example.ino (Take a copy of Util.h, Util.cpp with the ino)
#include "../Util/Util.h" // Uncomment this if you're working with Integration.ino

MQ2::MQ2(int analog, int warmup, int Threshold)
  : analogPin(analog), WarmupPeroid(warmup) {
  currentThreshold = MQSensitivityThresholds[Threshold];
}

MQ2::~MQ2() {}

// The MQ2's voltage-PPM curve is linear
// If the current reading is less than the current analog threshold, returns 0;
float MQ2::GetGasConcentration(bool realConc)
{
  Reading = analogRead(analogPin);
  if (Reading < currentThreshold) {
    Reading = 0;
    gasDetected = true;
  }
  else gasDetected = true;

  if (realConc)
    return mapfloat(Reading, analogVmin, analogVmax, MIN_PPM_MQ2, MAX_PPM_MQ2);
  else
  {
    return Reading;
  }
    
}

bool MQ2::IsGasDetected()
{
  return gasDetected;
}

void MQ2::PrintMQ2Data(bool plotter)
{
  float gasConc = GetGasConcentration(false);
  if (!plotter)
  {
    String output = "MQ2: PPM: ";
    output += String(gasConc, 2);
    if (IsGasDetected())
    {
      output += " | Gas detected!";
    }
    Serial.println(output);
  }
  else Serial.println(gasConc);
}

void MQ2::Warmup()
{
  delay(WarmupPeroid);
}

void MQ2::LowSensitivity()
{

}
