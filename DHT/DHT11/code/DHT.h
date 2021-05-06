#define DATA_PIN 3

unsigned char RH_int = 0, RH_dec = 0, T_int = 0, T_dec = 0, sum = 0;
unsigned char pulse[80];
bool ok = true;
void UpdateDHT();
void printT();
void printRH();
String getT();
String getRH();
int expectPulse(bool lvl);



int excpectedPulse(bool lvl)
{
  int count = 0;
  while(digitalRead(DATA_PIN) == lvl)
    count++;
   return count;
}
void UpdateDHT() 
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
    Serial.println("NOT RESPONDING");
    return;
  }
  ///////////////////////////////////////
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
      Serial.println("ERROR");
      ok = false;
    }
    else
    {
      ok = true;
    }
}

void printT()
{
  if (ok)
  {
    Serial.print("Temp : ");
    Serial.print(T_int);
    Serial.print(".");
    Serial.println(T_dec);
  }
}
void printRH()
{
  if (ok)
  {
    Serial.print("RH : ");
    Serial.print(RH_int);
    Serial.print(".");
    Serial.println(RH_dec);
  }
}
String getT()
{
  if(ok)
    return String(T_int)+'.'+String(T_dec);
  else 
    return "-";
}
String getRH()
{
  if(ok)
    return String(RH_int)+'.'+String(RH_dec);
  else return "-";
}


