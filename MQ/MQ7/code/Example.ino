#include "MQ7.h"

MQ7 Sensor(0, 2, 1000);

void setup()
{
  Serial.begin(9600);
  Serial.println("Gas sensor starting up!");  
  Sensor.Warmup();
}

void loop()
{
  int ppm = Sensor.GetGasConcentration();

  bool gasDetected = Sensor.IsGasDetected();
  
  Sensor.PrintMQ7Data();
}
