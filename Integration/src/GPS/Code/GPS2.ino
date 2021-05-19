#include "GPS.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);
GPS G(&mySerial);
void setup()
{
    Serial.begin(9600);
    Serial.println("Starting");
    mySerial.begin(9600);
}

void loop()
{
    if (millis() % 1000 == 0)
    {
        // G.NMEA();
        // G.DebugSatellites();
        G.readData();
        G.printAll();
    }
}
