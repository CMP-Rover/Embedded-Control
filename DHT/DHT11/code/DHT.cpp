#include "DHT.h"
#include "Arduino.h"

DHT::DHT(int pin = DATA_PIN)
{
    data_pin = pin;
}

void DHT::Initalize()
{
    pinMode(DATA_PIN,OUTPUT);
    digitalWrite(DATA_PIN,HIGH);
    delay(1000);
    digitalWrite(DATA_PIN,LOW);
    delay(18);
    digitalWrite(DATA_PIN,HIGH);
    delayMicroseconds(40);
    pinMode(DATA_PIN,INPUT);
    if (digitalRead(DATA_PIN) == LOW)
    {
        while(digitalRead(DATA_PIN) == LOW)
        {
        //delayMicroseconds(80);
        }
        while(digitalRead(DATA_PIN) == HIGH)
        {
        //delayMicroseconds(80);
        }
  }
  else
  {
    Serial.println("DHT NOT RESPONDING");
    return;
  }
}
void DHT::GetData()
{
    for (int i = 0;i < 80;i++)
  {
    pulse[i] = excpectedPulse(i%2);
  }
  for (int i = 0;i<40;i++)
  {
    unsigned char lowCycle = pulse[i*2];
    unsigned char highCycle = pulse[(i*2) + 1];
    if (i < 8)
    {
        RH_int <<=1;
        if (highCycle > lowCycle)
        {
            RH_int|=1;
        }
    }
    if (i < 16)
    {
        RH_dec <<=1;
        if (highCycle > lowCycle)
        {
            RH_dec|=1;
        }
    }
    if (i < 24)
    {
        T_int <<=1;
        if (highCycle > lowCycle)
        {
            T_int|=1;
        }
    }
    if (i < 32)
    {
        T_dec <<=1;
        if (highCycle > lowCycle)
        {
            T_dec|=1;
        }
    }
    if (i < 40)
    {
        sum <<=1;
        if (highCycle > lowCycle)
        {
            sum|=1;
        }
    }
  }
    if (sum != RH_int + RH_dec + T_int + T_dec)
    {
      Serial.println("ERROR: DHT reading is wrong");
      data_correct = false;
    }
    else
    {
      data_correct = true;
    }
}

unsigned char DHT:: getRH_int()
{
    return RH_int;
}

unsigned char DHT:: getRH_dec()
{
    return RH_dec
}

unsigned char DHT:: getT_int()
{
    return T_int;
}

unsigned char DHT:: getT_dec()
{
    return T_dec;
}

String DHT::getRH()
{
    return String(RH_int)+'.'+String(RH_dec);
}

String DHT::getT()
{
   return String(T_int)+'.'+String(T_dec);
}

void printT()
{
    Serial.print("Temp : ");
    Serial.print(T_int);
    Serial.print(".");
    Serial.println(T_dec);
}

void printRH()
{
    Serial.print("RH : ");
    Serial.print(RH_int);
    Serial.print(".");
    Serial.println(RH_dec);
}