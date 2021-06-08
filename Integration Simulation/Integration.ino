#include "src/Util/Util.h"
#include "src/BMP/Code/BMP180.h"
#include "src/GPS/Code/GPS2/GPS.h"
#include "src/motorsControl/Code/PID_Control.h"
#include "src/MQ/MQ7/code/MQ7.h"
#include "src/MQ/MQ2/code/MQ2.h"
#include "src/DHT/DHT11/DHT11/DHT.h"
#include "src/Sensors/Sensors.h"
#include <SoftwareSerial.h>

// GPS pins are from the GPS's prespective

#define GPS_RX 11
#define GPS_TX 10
#define MQ7_A A5                //was A12 in the MEGA (A2 for debugging on UNO only)
#define MQ2_A A1                //was A11
#define DHT_D 52


Sensors *sensors;

void setup()
{
  Serial.begin(9600);
  //SoftwareSerial * gpsserial;
  sensors = new Sensors(GPS_TX,GPS_RX,MQ7_A,MQ2_A,DHT_D);
  
}

void loop()
{
  //sensors->readGPS();
  sensors->PrintGPSData();
  sensors->readMQ7();
}
