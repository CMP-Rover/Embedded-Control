#pragma once
#include "Arduino.h"

// DEFAULT ARGUMENTS IN CPP ONLY

static int DHT_id = 0;
class DHT // for temperature and relative humedity "RH"
{

private:
    int data_pin;
    float temperature;
    float RH;
    ///////////////////////////////////////////////////////////////////
    unsigned char Pulse[64];
    unsigned char temperature_int, RH_int, temperature_dec, RH_dec;
    unsigned char expectPulse(bool level);
    ///////////////////////////////////////////////////////////////////
    void initialize();
    void assign_temperature();
    void assign_RH();

public:
    DHT(int pin);

    void set_temperature(float);
    void set_RH(float);

    int get_id();
    float get_temperature();
    float get_RH();

    void Read_data();                                   // should be used before getting any data
    bool Serial_print_data(bool Read_Data);         // if U want the sensor to read data again before printing or not
    bool Serial_print_data_LabView(bool Read_Data); // if U want the sensor to read data again before printing or not

    int temperature_cmp(DHT, int);
    int RH_cmp(DHT, int);

    bool operator==(DHT);
    bool operator!=(DHT);
    DHT operator+(DHT);
    DHT operator=(DHT);

    int get_data_pin();
    void set_data_pin(int);

    ~DHT(void);
};
