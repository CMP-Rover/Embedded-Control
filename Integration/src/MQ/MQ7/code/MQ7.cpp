#include "MQ7.h"
#include "Arduino.h"
#include "../../../Util/Util.h"
MQ7::MQ7(int analog = ANALOG_PIN, int digital = DIGITAL_PIN, int warmup = WARMUP_PERIOD)
{
    analog_pin = analog;
    digital_pin = digital;
    warmup_period = warmup;
}

// VOLTAGE PPM IS NOT LINEAR AAAAAAAAAAA
void MQ7::GetGasConcentration(int &analogReading, float &mappedVoltage, float &mappedPPM)
{
    analogReading = analogRead(ANALOG_PIN);
    mappedVoltage = mapfloat(analogReading, 0, 1023, 0, 5); // Map analog to voltage
    mappedPPM = mapfloat(mappedVoltage, MIN_OUTPUT, MAX_OUTPUT, MIN_PPM_MQ7, MAX_PPM_MQ7);
}

bool MQ7::IsGasDetected()
{
    pinMode(digital_pin, INPUT);
    return digitalRead(digital_pin);
}

void MQ7::PrintMQ7Data()
{
    int analog;
    float voltage, PPM;
    String output = "MQ7:";

    GetGasConcentration(analog, voltage, PPM);

    output += /*" mapped PPM: " + String(PPM, 3) + */ " analog reading: " + String(analog, DEC) ; /*+ ", mapped voltage: " + String(voltage, 3);*/

    if (IsGasDetected())
    {
        output += " | Gas detected!";
    }

    Serial.println(output);
}

void MQ7::Warmup()
{
    delay(warmup_period);
}

MQ7::~MQ7()
{
}
