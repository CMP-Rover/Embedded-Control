#include "GPS.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3);
GPS G(&mySerial);
void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600);
}

void loop()
{
    if (millis() % 10000 == 0)
    {
        G.readData();
        G.printAll();
    }
}
