#include "src/Sensors/Sensors.h"
#include "src/GndControlOptimized/GndControlOptimized.h"

// GPS pins are from the GPS's prespective

#define GPS_RX 11
#define GPS_TX 10
#define MQ7_A A5 //was A12 in the MEGA (A2 for debugging on UNO only)
#define MQ2_A A1 //was A11
#define DHT_D 3

Sensors *sensors;

void setup()
{
  for (int i = 40; i <= 51; i++)
  {
    pinMode(i, OUTPUT);
  }
  for (int i = 4; i <= 9; i++)
  {
    pinMode(i, OUTPUT);
  }

  Serial.begin(9600); // Initiates the serial to do the monitoring
  Serial.println("Begin motor control");
  //SoftwareSerial * gpsserial;
  sensors = new Sensors(GPS_TX, GPS_RX, MQ7_A, MQ2_A, DHT_D);
}

void loop()
{
  sensors->readGPS(true);
  sensors->PrintGPSData();
  sensors->readMQ7();
  sensors->readDHT();
  Serial.println(sensors->DHT_rh);
  Serial.println(sensors->DHT_Temperature);
  delay(500);
  
  // Motor control
  turn(12);
}
