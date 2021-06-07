#include "MQ7.h"
#include "Arduino.h"
// #include "Util.h" // Uncomment this if you're working with MQ7's example.ino (Take a copy of Util.h, Util.cpp with the ino)
#include "../Util/Util.h" // Uncomment this if you're working with Integration.ino
MQ7::MQ7(int analog = ANALOG_PIN, int warmup = WARMUP_PERIOD, int threshold = Med)
{
  analog_pin = analog;
  warmup_period = warmup;
  detectionThreshold = threshold;
}

// VOLTAGE PPM IS NOT LINEAR AAAAAAAAAAA
void MQ7::GetGasConcentration(float &mappedVoltage, float &mappedPPM, bool mapToPPM)
{
  analog_value = analogRead(analog_pin);
  if (analog_value < MQSensitivityThresholds[detectionThreshold])
  {
    analog_value = 0;
    gasDetected = false;
  }
  else
  {
    gasDetected = true;
  }

  if (mapToPPM)
  {
    mappedVoltage = mapfloat(analog_value, 0, 1023, 2.5, 4.3); // Map analog to voltage
    mappedPPM = mapfloat(mappedVoltage, MIN_OUTPUT, MAX_OUTPUT, 0, 50);
  }
}

bool MQ7::IsGasDetected()
{
  return gasDetected;
}

void MQ7::PrintMQ7Data(bool plotter)
{
  float voltage, PPM;
  GetGasConcentration( voltage, PPM, false);

  if (!plotter)
  {
    String output = "MQ7:";

    output += /*" mapped PPM: " + String(PPM, 3) + */ " analog reading: " + String(analog_value, DEC) ; /*+ ", mapped voltage: " + String(voltage, 3);*/

    if (IsGasDetected())
    {
      output += " | Gas detected!";
    }

    Serial.println(output);
  }
  else Serial.println(analog_value);
}

void MQ7::Warmup()
{
  delay(warmup_period);
}

MQ7::~MQ7()
{
}
