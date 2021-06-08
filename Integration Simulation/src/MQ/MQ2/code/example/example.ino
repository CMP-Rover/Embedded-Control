#include "MQ2.h"
#define ReadingInterval 250  // Just so the serial monitor doesn't go crazy


// Creating an MQ2 sensor object
// (analogPin, digitalPin, warmupPeroid [in ms], Sensitivity (Low, Med, Hi))
MQ2 gasSensor(0, 2000, Low);


void setup() {
  Serial.begin(9600);  // sets the serial port to 9600
  //Serial.println("Gas sensor warming up!");

  // Calls delay(WarmupPeroid) internally.
  gasSensor.Warmup();
}

void loop() {

  // reads the gas concentration from the sensor's analog pin, returns a value (0-1023)
  float conc = gasSensor.GetGasConcentration(false);

  // Reads the digital pin which is HIGH or LOW depending on whether gas is past the
  // configured concentration.
  bool gasDetected = gasSensor.IsGasDetected();

  // Gets the data and prints, all in one go
  // If passed false, prints the analog reading and whether gas is detected or not.
  // If passed true, only prints the analog reading, used for plotting.
  gasSensor.PrintMQ2Data(true);

  delay(ReadingInterval);  // wait 1s for next reading
}
