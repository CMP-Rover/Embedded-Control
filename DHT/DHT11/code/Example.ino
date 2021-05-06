#include "DHTlib.h"
#include "SDlib.h"
void printContent(String content)
{
    Serial.println(content.toFloat());
}
void setup()
{
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Setup");
  
  UpdateDHT();
  String T = getT();
  String RH = getRH();
}

void loop()
{
  
}
