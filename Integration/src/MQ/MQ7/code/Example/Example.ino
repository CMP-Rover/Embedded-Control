#include "MQ7.h"

MQ7 Sensor(1, 1000, Low);

void setup()
{
  Serial.begin(9600);
//  Serial.println("Gas sensor starting up!");  
  Sensor.Warmup();
}

void loop()
{
  Sensor.PrintMQ7Data(true);
  delay(250);
}
