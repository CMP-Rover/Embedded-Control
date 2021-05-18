#include "DHT.h"

DHT* Pdht=new DHT(2);
void setup()
{
  Serial.begin(115200);

}
void loop()
{
  Pdht->Serial_print_data();
}
