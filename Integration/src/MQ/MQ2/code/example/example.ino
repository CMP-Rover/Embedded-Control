#include "MQ2.h"
#define ReadingInterval 250  // Just so the serial monitor doesn't go crazy


// Creating an MQ2 sensor object
// (analogPin, digitalPin, warmupPeroid [in ms])
MQ2 gasSensor(0, 7, 2000);


void setup() {
  Serial.begin(9600);  // sets the serial port to 9600
  //Serial.println("Gas sensor warming up!");

  // Calls delay(WarmupPeroid) internally.
  gasSensor.Warmup();
}

void loop() {

  // reads the gas concentration from the sensor's analog pin, returns a value (0-1023)
  float conc = gasSensor.GetGasConcentration();

  // Reads the digital pin which is HIGH or LOW depending on whether gas is past the
  // configured concentration.
  bool gasDetected = gasSensor.IsGasDetected();

  // Gets the data and prints, all in one go
  gasSensor.PrintMQ2Data();

  delay(ReadingInterval);  // wait 1s for next reading
}
