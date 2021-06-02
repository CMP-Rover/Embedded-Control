#include "src/Util/Util.h"
#include "src/BMP/Code/BMP180.h"
#include "src/GPS/Code/GPS2/GPS.h"
#include "src/motorsControl/Code/PID_Control.h"
#include "src/MQ/MQ7/code/MQ7.h"
#include "src/MQ/MQ2/code/MQ2.h"
#include "src/DHT/DHT11/DHT11/DHT.h"
#include <SoftwareSerial.h>




SoftwareSerial mySerial(5, 6); // To be changed
GPS *Pgps = new GPS(&mySerial);
MQ7 *Pmq7 = new MQ7(14, 53, 1000);
MQ2 *Pmq2 = new MQ2(15, 33, 2000);
DHT *Pdht = new DHT(52);

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  Pmq2->Warmup();
  Pmq7->Warmup();
}

void loop()
{
  int x = millis();
  int i = 0;
  if (i % 5000 == 0)
  {
    float temp = 0, pressure = 0, altitude = 0;
    unsigned char RH_int, T_int, RH_dec, T_dec;
    int DHTData = 0;
    
    //MQ7
    Pmq7->PrintMQ7Data(true);

    //MQ2
    Pmq2->PrintMQ2Data(true);

    //DHT
    Pdht->Serial_print_data();

    if ((x - 11000) > 0)
    {
      Pgps->readData(150);
      Serial.print("Position: ");
      Pgps->printAll();
    }

    Serial.print("Temperature:");
    Serial.println(temp);
    Serial.print("Pressure:");
    Serial.println(pressure / 100.0);
    Serial.print("Altitude:");
    Serial.println(altitude);
    Serial.println("End!");
    Serial.println("--------------------------------------------");
    i++;
  }
}
