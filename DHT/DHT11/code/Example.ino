#include "DHT.h"

DHT D1(3);
void setup()
{
  Serial.begin(9600);;
}

void loop()
{
  D1.printT();
  D1.printRH();
}
