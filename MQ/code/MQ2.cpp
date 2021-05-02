#include "MQ2.h"
#include "Arduino.h"

MQ2::MQ2(int analog, int digital, int warmup)
    : analogPin(analog), digitalPin(digital), WarmupPeroid(warmup) {}

MQ2::~MQ2() {}

int MQ2::GetGasConcentration()
{
    return analogRead(analogPin);
}

bool MQ2::IsGasDetected()
{
    pinMode(digitalPin, INPUT);
    return digitalRead(digitalPin);
}

void MQ2::PrintMQ2Data()
{
    int gasConc = GetGasConcentration();
    Serial.print("Sensor Value: ");
    Serial.print(gasConc);

    if (IsGasDetected())
    {
        Serial.print(" | Gas detected!");
    }

    Serial.println("");
}

void MQ2::Warmup()
{
    delay(WarmupPeroid);
}