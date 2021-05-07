#include "MQ7.h"
#include "Arduino.h"
MQ7::MQ7(int analog = ANALOG_PIN, int digital = DIGITAL_PIN, int warmup = WARMUP_PERIOD)
{
    analog_pin = analog;
    digital_pin = digital;
    warmup_period = warmup;
}



int MQ7::GetGasConcentration()
{
    int value = analogRead(analog_pin);
    if (value >= MAX_OUTPUT)
        value = MAX_OUTPUT;
    else if (value <= MIN_OUTPUT)
        value = MIN_OUTPUT;
    // 4.3 --> 500 ppm
    // value --> ? ppm

    return ( (value * 500) / 4.3 );
}

bool MQ7::IsGasDetected()
{
    pinMode(digital_pin, INPUT);
    return digitalRead(digital_pin);
}

void MQ7::PrintMQ7Data(int data,bool detected)
{
    int PPM = GetGasConcentration();
    data=PPM;
    Serial.print("CO: ");
    Serial.print(PPM);
    Serial.print(" ppm");
    detected=IsGasDetected();
    if (detected)
    {
        Serial.println(" | Gas detected!");
    }

    Serial.println("");
}

void MQ7::Warmup()
{
    delay(warmup_period);
}


MQ7::~MQ7()
{

}
