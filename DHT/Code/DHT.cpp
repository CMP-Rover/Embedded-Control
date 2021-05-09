#include "DHT.h"
#include "Arduino.h"

DHT::DHT(int pin = DATA_PIN)
{
    data_pin = pin;
}

int DHT::excpectedPulse(bool lvl)
{
  int count = 0;
  while(digitalRead(data_pin) == lvl)
    count++;
   return count;
}

void DHT::GetData()
{
    pinMode(data_pin,OUTPUT);
    digitalWrite(data_pin,HIGH);
    delay(1000);
    digitalWrite(data_pin,LOW);
    delay(18);
    digitalWrite(data_pin,HIGH);
    delayMicroseconds(40);
    pinMode(data_pin,INPUT);
    if (digitalRead(data_pin) == LOW)
    {
        while(digitalRead(data_pin) == LOW)
        {
        //delayMicroseconds(80);
        }
        while(digitalRead(data_pin) == HIGH)
        {
        //delayMicroseconds(80);
        }
  }
  else
  {
    Serial.println("DHT NOT RESPONDING");
    return;
  }
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
    return RH_dec;
}

unsigned char DHT:: getT_int()
{
    return T_int;
}

unsigned char DHT:: getT_dec()
{
    return T_dec;
}

void DHT::printT()
{
    Serial.print("Temp : ");
    Serial.print(T_int);
    Serial.print(".");
    Serial.println(T_dec);
}
void DHT::printRH()
{
    Serial.print("RH : ");
    Serial.print(RH_int);
    Serial.print(".");
    Serial.println(RH_dec);
}
