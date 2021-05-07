#include "DHT.h"

DHT D1(10);
void setup()
{
  Serial.begin(9600);

}
void loop()
{
  D1.GetData();
  D1.printT();
  D1.printRH();
}
