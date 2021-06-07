#include "DHT.h"

/**************************-**********************************
*                               *
           Utility functions
*                              *
***************************-*********************************/
unsigned char DHT::expectPulse(bool level)
{
  unsigned char count = 0;
  int i = 0;
  while (digitalRead(data_pin) == level)
  {
    count++;
    i++;
    if (i == 64)
      break;
  }
  return count;
}
/**************************-**********************************
*                              *
          Initialization
*                              *
***************************-*********************************/
// A ctr which takes the data pin and initialized to pin 0
DHT::DHT(int pin = 0)
{
  data_pin = pin; // assigning the pin
  DHT_id++;       // incrementing number of DHTs and assign them IDs
}
//initializing the sensor and reading data , N.B : check the datasheet for more details , requires intialization every time reading the data
void DHT::initialize()
{

  //To save the time of every response of DHT

  pinMode(data_pin, OUTPUT); //1) apply a high voltage to the sensor and give the sensor a chance to feel the high volt
  digitalWrite(data_pin, HIGH);
  delay(150);
  digitalWrite(data_pin, LOW); //2) Send a starting signal by pulling the signal from high to low "from datasheet it takes 18 ms to make DHT feel it"
  delay(18);
  digitalWrite(data_pin, HIGH); //3) Then MCU will pull up voltage and wait 20-40us for DHT’s response.
  delayMicroseconds(40);
  pinMode(data_pin, INPUT);

  if (digitalRead(data_pin) == LOW)
  {
    while (digitalRead(data_pin) == LOW) // waiting DHT to pull down voltage and keep it for 80us
    {
      //delayMicroseconds(80);
    }
    while (digitalRead(data_pin) == HIGH) // waiting DHT to pull up voltage and keep it for 80us
    {
      //delayMicroseconds(80);
    }
  }
}
void DHT::Read_data()
{
  initialize(); //we should initialize the sensor every time before reading the data

  /*-------------------------------------------*/
  // 1) Save Data from DHT in array "Pulse[]"

  for (int i = 0; i < 64; i++)
  {
    Pulse[i] = expectPulse(i % 2);
  } // every bit has two sections, and we have 40 bit so we have 80 sections

  // 2) Determination of 1s and 0s & storing the data
  for (int i = 0; i < 32; i++)
  {
    unsigned char lowCycles = Pulse[2 * i];
    unsigned char highCycles = Pulse[2 * i + 1];

    if (i < 8)
    {
      RH_int <<= 1; //Shifting RH_int to store the next 0 or 1
      if (highCycles > lowCycles)
        RH_int |= 1; // High cycles are greater than 50us low cycle count, must be a 1. put 1 in RH_int
    }
    else if (i < 16)
    {
      RH_dec <<= 1; //shift RH_dec
      if (highCycles > lowCycles)
        RH_dec |= 1; // High cycles are greater than 50us low cycle count, must be a 1.
    }
    else if (i < 24)
    {
      temperature_int <<= 1;
      if (highCycles > lowCycles)
        temperature_int |= 1;
    }
    else if (i < 32)
    {
      temperature_dec <<= 1;
      if (highCycles > lowCycles)
        temperature_dec |= 1;
    }
  }

  //digitalWrite(data_pin,HIGH);  /* A condition to declare that reading data is finished check the datasheet*/
  /*-------------------------------------------*/
  /*assigning the data in the temperature and relative humedity variables*/
  assign_temperature();
  assign_RH();
}
/**************************-**********************************
*                              *
    Assiging the calculated data in the variables
*                              *
***************************-*********************************/
void DHT::assign_temperature()
{
  temperature = (temperature_int) + (temperature_dec) / 100.0;
}
void DHT::assign_RH()
{
  RH = (RH_int) + (RH_dec) / 100.0;
}
/**************************-**********************************
*                              *
            Setters
*                              *
***************************-*********************************/
void DHT::set_temperature(float t)
{
  temperature = t;
}
void DHT::set_RH(float r)
{
  RH = r;
}
/**************************-**********************************
*                              *
            Getters
*                              *
***************************-*********************************/
int DHT::get_id()
{
  return DHT_id;
}
float DHT::get_temperature()
{
  return temperature;
}
float DHT::get_RH()
{
  return RH;
}

//print the data on the serial monitor
bool DHT::Serial_print_data(bool Read_Data = 1)
{
  if (Read_Data)
  {
    Read_data();
  }
  if (temperature_int >= 100)
    return true;
  Serial.print("DHT: ");
  Serial.write("RH = ");
  Serial.print(RH_int);
  Serial.print(".");
  Serial.print(RH_dec);
  Serial.write("  Temperature  = ");
  Serial.print(temperature_int);
  Serial.print(".");
  Serial.print(temperature_dec);
  Serial.println("  ");

  /*
  Serial.print("DHT: ");
  Serial.write("RH = "); Serial.print(RH);
  Serial.write(" Temperature  = ");Serial.print(temperature); Serial.print(" C");
  Serial.println ("  ");
  */
  return true;
}

bool DHT::Serial_print_data_LabView(bool Read_Data = 1)
{
  if (Read_Data)
  {
    Read_data();
  }

  Serial.print("DHT,");
  Serial.print(RH);
  Serial.write(",");
  Serial.print(temperature);
  Serial.println("  ");
  return true;
}
/**************************-**********************************
*                              *
       Overloaded operators & compare operations
*                              *
***************************-*********************************/
//compares the data of the 2-DHTs relative to their average readings with a given error percentage (default is 10%)
int DHT::temperature_cmp(DHT passed, int error = 10)
{
  if ((error > 0 && error < 101))
    error = 10;

  float temperature_error = ((temperature + passed.get_temperature()) / 200 * error);
  if ((temperature > passed.get_temperature()) > temperature_error)
    return 1;
  if ((temperature > passed.get_temperature()) < temperature_error)
    return -1;
  return 0;
}
int DHT::RH_cmp(DHT passed, int error)
{
  if ((error > 0 && error < 101))
    error = 10;

  float RH_error = ((RH + passed.get_RH()) / 200 * error);
  if ((RH > passed.get_RH()) > RH_error)
    return 1;
  if ((RH > passed.get_RH()) < RH_error)
    return -1;
  return 0;
}

// compares whether the 2-DHTs read the same data values or not with an error percentage 10%
bool DHT::operator==(DHT passed)
{
  return (RH_cmp(passed, 10) && temperature_cmp(passed, 10));
}
bool DHT::operator!=(DHT passed)
{
  return (!(*this == passed));
}

//sets the temperature and RH values of the RHS to the LHS
DHT DHT::operator=(DHT passed)
{
  set_temperature(passed.get_temperature());
  set_RH(passed.get_RH());
}
// returns a new DHT which has the average values of temperature and RH of the 2-passed DHTs
DHT DHT::operator+(DHT passed)
{
  DHT tempo;
  tempo.set_temperature((get_temperature() + passed.get_temperature()) / 2);
  tempo.set_RH((get_RH() + passed.get_RH()) / 2);
  return tempo;
}

/**************************-**********************************
*                              *
        Some pin operations
*                              *
***************************-*********************************/
int DHT::get_data_pin()
{
  return data_pin;
}
void DHT::set_data_pin(int p)
{
  data_pin = p;
}

DHT::~DHT(void)
{
}
