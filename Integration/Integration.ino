#include"BMP180.h"
#include "GPS.h"
#include "PID_Control.h"
#include "MQ7.h"
#include "MQ2.h"
#include "DHT.h"
#include <SPI.h>
#include <SD.h>

#define ENCODER_A 2
#define ENCODER_B 3
#define PWM 5
#define IN2 6
#define IN1 7

_BMP180_ bmpp;
GPS G;
MQ7 Sensor(0, 8, 1000);
MQ2 gasSensor(0, 9, 2000);
DHT D1(4);
File file;

void setup()
{
  Serial.begin(9600);
  bmpp.begin();
  Sensor.Warmup();
  pinMode(ENCODER_A, INPUT); // ENCODER_A as Input
  pinMode(ENCODER_B, INPUT); // ENCODER_B as Input
  pinMode(IN2, OUTPUT); // MOTOR_CW as Output
  pinMode(IN1, OUTPUT); // MOTOR_CW as Output
  pinMode(PWM, OUTPUT); // MOTOR_CW as Output
  setPIDTarget(400);
  setPIDParameters (24, 0, 16);
  setMotorEncoders(ENCODER_A, ENCODER_B);
  attachInterrupt(digitalPinToInterrupt(ENCODER_A), readEncoder, RISING);
  gasSensor.Warmup();
  if (SD.begin(10))
  {
    if(SD.exists("data.txt"))
    {
      SD.remove("data.txt");
    }
    Serial.println("Card initialized!");
  }
  digitalWrite(10, HIGH);
}

void loop()
{
  int x = millis();
  int i = 0;
  float pos = getCurrentPosition();
  float conSignal = computePID(pos);
  convertSignal(conSignal , PWM ,  IN1 , IN2);
  if (i % 5000 == 0)
  {
    float temp = 0, pressure = 0, altitude = 0;
    int MQ2Data = 0 , MQ7Data = 0, DHTData = 0;
    bool MQ2Detected = false , MQ7Detected = false;
    unsigned char RH_int, T_int, RH_dec, T_dec;
    bmpp.getTemperature(&temp);
    bmpp.getPressure(&pressure);
    altitude = bmpp.pressureToAltitude(101325, pressure);
    //MQ7
    Sensor.PrintMQ7Data(&MQ7Data, &MQ7Detected);
    //MQ2
    gasSensor.PrintMQ2Data(&MQ2Data, &MQ2Detected);
    //DHT
    D1.GetData();
    D1.printT(&T_int, &T_dec);
    D1.printRH(&RH_int, &RH_dec);
    if ((x - 11000) > 0)
    {
      G.readData(150);
      Serial.print("Position: ");
      G.printAll();
    }
    Serial.print("Temperature:");
    Serial.println(temp);
    Serial.print("Pressure:");
    Serial.println(pressure / 100.0);
    Serial.print("Altitude:");
    Serial.println(altitude);
    Serial.print("Pos : ");
    Serial.println(pos);

    file = SD.open("data.txt", FILE_WRITE);
    if (!file)
    {
      Serial.println("File not detected!");
    }
    else
    {
      Serial.println("Printing...");
      file.print("Temperature:");
      file.println(String(temp));
      file.print("Pressure:");
      file.println(String(pressure / 100.0));
      file.print("Altitude:");
      file.println(String(altitude));
      file.print("Pos : ");
      file.println(String(pos));
      file.println("--------------------------------------------");
      file.close();
    }
    Serial.println("End!");
    Serial.println("--------------------------------------------");
  }
  i++;
}
