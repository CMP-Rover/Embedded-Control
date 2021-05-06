#include"BMP180.h"
#include "GPS.h"
#include "PID_Control.h"
#include "MQ7.h"
#include "MQ2.h"
#include "DHT.h"
#define ENCODER_A 2
#define ENCODER_B 3
#define PWM 5
#define IN2 6
#define IN1 7
_BMP180_ bmpp;
GPS G;
MQ7 Sensor(0, 2, 1000);
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
    bmpp.getTemperature(&temp);
    bmpp.getPressure(&pressure);
    altitude = bmpp.pressureToAltitude(101325, pressure);
    int ppm = Sensor.GetGasConcentration();
    bool gasDetected = Sensor.IsGasDetected();
    //    Sensor.PrintMQ7Data();
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
  }
  i++;
}
