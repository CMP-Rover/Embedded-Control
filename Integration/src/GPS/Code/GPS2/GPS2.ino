#include "GPS.h"
#include <SoftwareSerial.h>
SoftwareSerial mySerial(5, 11);
GPS G(&mySerial);
unsigned long start;
String gpsPosition;
void setup()
{
    Serial.begin(9600);
    Serial.println("Starting");
    mySerial.begin(9600);
    while(!G.DebugSatellites()){}
    start = millis();
    
}

void loop()
{
  Serial.println("some computing...");

    if (millis() - start > 10000)
    {
        // G.NMEA();
        // G.DebugSatellites();
        G.readData(500);
        G.printAll();
        gpsPosition = G.getPosition();
        start = millis();
    }
}
