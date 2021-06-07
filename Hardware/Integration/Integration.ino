#include "src/Sensors/Sensors.h"
#include "src/GndControlOptimized/GndControlOptimized.h"
#include "src/Encoder/enc.h"

// pins
// GPS pins are from the GPS's prespective
#define GPS_RX 11
#define GPS_TX 10
#define MQ7_A A5 //was A12 in the MEGA (A2 for debugging on UNO only)
#define MQ2_A A1 //was A11
#define DHT_D 13 /////
//  motors
#define ENC_IN1 2
#define ENC_IN2 18
#define ENC_IN3 19
#define ENC_IN4 21
#define ENC_IN5 3
#define ENC_IN6 20
motorEnc en1(40, 41, 4);
motorEnc en2(42, 43, 5);
motorEnc en3(46, 47, 7);
motorEnc en4(44, 45, 6);
motorEnc en5(48, 49, 8);
motorEnc en6(50, 51, 9);
int RPM1 = 0;
int RPM2 = 0;
int RPM3 = 0;
int RPM4 = 0;
int RPM5 = 0;
int RPM6 = 0;
//
Sensors *sensors;
///////////////////
// to be use by ros
///////////////////
bool ground = false;
//
int reqRPM1 = 00;
int reqRPM2 = 00;
int reqRPM3 = 00;
int reqRPM4 = 00;
int reqRPM5 = 00;
int reqRPM6 = 00;
//
//
int readRPM1 = 0;
int readRPM2 = 0;
int readRPM3 = 0;
int readRPM4 = 0;
int readRPM5 = 0;
int readRPM6 = 0;
int Degrees = 1;
float Speed = 1;
void setup()
{

  Serial.begin(9600); // Initiates the serial to do the monitoring
  //SoftwareSerial * gpsserial;
  sensors = new Sensors(GPS_TX, GPS_RX, MQ7_A, MQ2_A, DHT_D);
  //motors
  // motors pins
  for (int i = 40; i <= 51; i++)
  {
    pinMode(i, OUTPUT);
  }
  for (int i = 4; i <= 9; i++)
  {
    pinMode(i, OUTPUT);
  }
  // encoders
  pinMode(ENC_IN1, INPUT_PULLUP);
  pinMode(ENC_IN2, INPUT_PULLUP);
  pinMode(ENC_IN3, INPUT_PULLUP);
  pinMode(ENC_IN4, INPUT_PULLUP);
  pinMode(ENC_IN5, INPUT_PULLUP);
  pinMode(ENC_IN6, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENC_IN1), updateEncoder1, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_IN2), updateEncoder2, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_IN3), updateEncoder3, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_IN4), updateEncoder4, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_IN5), updateEncoder5, RISING);
  attachInterrupt(digitalPinToInterrupt(ENC_IN6), updateEncoder6, RISING);
}

void loop()
{
  if (ground)
  {
//    sensors->readGPS(true);
//    sensors->PrintGPSData();
//    sensors->readMQ7();
//    sensors->readDHT();
//    delay(500);

    // Motor control
    turn(Degrees, Speed);
  }
  else
  {

    if (reqRPM1 != RPM1)
    {
      RPM1 = reqRPM1;
      en1.reachedRequired = false;
    }
    if (reqRPM2 != RPM2)
    {
      RPM2 = reqRPM2;
      en2.reachedRequired = false;
    }
    if (reqRPM3 != RPM3)
    {
      RPM3 = reqRPM3;
      en3.reachedRequired = false;
    }
    if (reqRPM4 != RPM4)
    {
      RPM4 = reqRPM4;
      en4.reachedRequired = false;
    }
    if (reqRPM5 != RPM5)
    {
      RPM5 = reqRPM5;
      en5.reachedRequired = false;
    }
    if (reqRPM6 != RPM6)
    {
      RPM6 = reqRPM6;
      en6.reachedRequired = false;
    }
    if (RPM1 > 0)
      en1.CCW();
    else
      en1.CW();
    if (RPM2 > 0)
      en2.CCW();
    else
      en2.CW();
    if (RPM3 > 0)
      en3.CCW();
    else
      en3.CW();
    if (RPM5 > 0)
      en5.CCW();
    else
      en5.CW();
    if (RPM6 > 0)
      en6.CCW();
    else
      en6.CW();
    if (RPM4 > 0)
      en4.CCW();
    else
      en4.CW();
  }
  readRPM1 = en1.setRPM(RPM1);
  readRPM2 = en2.setRPM(RPM2);
  readRPM3 = en3.setRPM(RPM3);
  readRPM4 = en4.setRPM(RPM4);
  readRPM5 = en5.setRPM(RPM5);
  readRPM6 = en6.setRPM(RPM6);
}
void updateEncoder1()
{
  // Increment value for each pulse from encoder
  en1.encoderValue++;
}
void updateEncoder2()
{
  // Increment value for each pulse from encoder
  en2.encoderValue++;
}
void updateEncoder3()
{
  // Increment value for each pulse from encoder
  en3.encoderValue++;
}
void updateEncoder4()
{
  // Increment value for each pulse from encoder
  en4.encoderValue++;
}
void updateEncoder5()
{
  // Increment value for each pulse from encoder
  en5.encoderValue++;
}
void updateEncoder6()
{
  // Increment value for each pulse from encoder
  en6.encoderValue++;
}
