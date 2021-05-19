#ifndef _GPS_H
#define _GPS_H

#include <stdlib.h>
#include"Arduino.h"
#include<SoftwareSerial.h>
/// GPS location is defined by latitude خط عرض and longitude خط طول \n
/// It takes about 10 -15 seconds at the beginning till readings become accurate \n
/// Connect GPS TX to arduino's RX and connect Serial TX to arduino's TX \n
///          |         |         |         |         |         |         |   \n
/// 012345678901234567890123456789012345678901234567890123456789012345678901 \n
///$GPGGA,033410.000,2232.1745,N,11401.1920,E,1,07,1.1,107.14,M,0.00,M,,*64' \n
///                  ddmm.mmmm   dddmm.mmmm

class GPS
{
private:
    double latitude;
    double longitude;
    SoftwareSerial *mySerial;
public:

/// Constructor
/// @param mySerial: of type SoftwareSerial, you should create an object of SoftwareSerial and 
/// pass it by pointer to the GPS.
/// # Example:
/// ~~~~~~~~~~~ {.cpp}
/// SoftwareSerial mySerial(2,3);
/// GPS myGPS(&mySerial);
/// ~~~~~~~~~~~
/// connect rx of mySerial to tx of GPS and tx of mySerial to rx of GPS
GPS(SoftwareSerial*mySerial);
/// get the latitude 
double getLatitude();
/// get the longitude
double getLongitude();
/// it takes 100 ms to read data, so it's a big delay.\n Use it once a while to update readings (i.e. once a minute).
/// or use GPS::readEachMS()
/// @param duration: duration it takes to wait for data. default: 500 ms
void readData(unsigned long duration = 500);

/// read true values every duration ms
/// @param freq: data reading frequency in milli seconds. default: once each 10 seconds (optional)
/// @param duration: like readData (optional)
/// return true if read new data
/// this function will read starting from 11th second. as before it: data is not ready yet
bool readPer(unsigned long freq = 10000,unsigned long duration = 500);

/// print on Serial monitor
void printAll();
/// Get position which you can put into Google maps
String getPosition();
/// print NMEA syntax
void NMEA();

/// Debug number of satellites
void DebugSatellites();
};

#endif
