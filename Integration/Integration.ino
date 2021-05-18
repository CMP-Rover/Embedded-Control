#include "src/Util/Util.h"
#include "src/BMP/Code/BMP180.h"
#include "src/GPS/Code/GPS.h"
#include "src/motorsControl/Code/PID_Control.h"
#include "src/MQ/MQ7/code/MQ7.h"
#include "src/MQ/MQ2/code/MQ2.h"
#include "src/DHT/DHT11/code/DHT.h"

#define ENCODER_A 2
#define ENCODER_B 3
#define PWM 5
#define IN2 6
#define IN1 7

_BMP180_* Pbmp = new _BMP180_();
GPS* Pgps = new GPS();
MQ7* Pmq7 = new MQ7(0, 8, 1000);
MQ2* Pmq2 = new MQ2(0, 9, 2000);
DHT* Pdht=new DHT(53);


void setup()
{
  Serial.begin(9600);
  Pbmp->begin();
  Pmq2->Warmup();
  Pmq7->Warmup();

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
    unsigned char RH_int, T_int, RH_dec, T_dec;
    int DHTData = 0;

    // BMP
    Pbmp->getTemperature(&temp);
    Pbmp->getPressure(&pressure);
    altitude = Pbmp->pressureToAltitude(101325, pressure);

    //MQ7
    Pmq7->PrintMQ7Data();

    //MQ2
    //Pmq2->PrintMQ2Data();

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
    Serial.print("Pos : ");
    Serial.println(pos);


    Serial.println("End!");
    Serial.println("--------------------------------------------");
    i++;
  }

}
