#include "GPS.h"

GPS::GPS(SoftwareSerial *mySerial)
{
    latitude = 0.0;
    longitude = 0.0;
    this->mySerial = mySerial;
}
double GPS::getLatitude()
{
    return latitude;
}
double GPS::getLongitude()
{
    return longitude;
}
void GPS::readData(unsigned long duration)
{
    char reading[72];

    // it takes about duration ms for it to read all NMEA sentences
    for (unsigned long start = millis(); millis() - start < duration;)
    {
        while (mySerial->available())
        {
            // a start of NMEA sentence
            if (mySerial->read() == '$')
            {
                // read a complete sentence
                mySerial->readBytesUntil('\n', reading, 72);
                reading[71] = '\0';

                // reading latitude and longitude
                if (reading[2] == 'G' && reading[3] == 'G' && reading[4] == 'A')
                {
                    double temp;
                    int inCount = 0;
                    //find latitude and longitude
                    for (int i = 0; i < strlen(reading); i++)
                    {
                        if (reading[i] == ',')
                        {
                            temp = atof(reading + i + 1);
                            inCount++;
                        }
                        if (inCount == 2)
                        {
                            latitude = temp;
                        }
                        if (inCount == 4)
                        {
                            longitude = temp;
                            break;
                        }
                    }
                    // convert to degrees and minutes
                    int integerPart = ((int)latitude / 100);
                    latitude = integerPart + ((latitude)-integerPart * 100) / 60.0;

                    // longitude = atof(reading + 29);
                    integerPart = ((int)longitude / 100);
                    longitude = integerPart + ((longitude)-integerPart * 100) / 60.0;
                }
            }
            break;
        }
    }
}
void GPS::printAll()
{
    Serial.print(latitude, 6);
    Serial.print(", ");
    Serial.print(longitude, 6);
    Serial.println();
}

String GPS::getPosition()
{
    return String(latitude, 6) + ", " + String(longitude, 6);
}

bool GPS::readPer(unsigned long freq, unsigned long duration)
{
    if ((millis() - 11000) % freq == 0)
    {
        readData(duration);
        return true;
    }
    return false;
}
void GPS::NMEA()
{
    char reading[72];

    // it takes about duration ms for it to read all NMEA sentences
    for (unsigned long start = millis(); millis() - start < 500;)
    {
        while (mySerial->available())
        {
            // a start of NMEA sentence
            if (mySerial->read() == '$')
            {
                // read a complete sentence
                mySerial->readBytesUntil('\n', reading, 72);
                reading[71] = '\0';
                Serial.println(reading);
            }
            break;
        }
    }
}
bool GPS::DebugSatellites()
{
    char reading[72];
    bool found = false;
    // it takes about duration ms for it to read all NMEA sentences
    for (unsigned long start = millis(); millis() - start < 500;)
    {
        while (mySerial->available())
        {
            // a start of NMEA sentence
            if (mySerial->read() == '$')
            {
                // read a complete sentence
                mySerial->readBytesUntil('\n', reading, 72);
                reading[71] = '\0';

                if (reading[2] == 'G' && reading[3] == 'S' && reading[4] == 'V')
                {
                    found = true;
                    int temp;
                    int numSatellites = 0;
                    int inCount = 0;
                    //find latitude and longitude
                    for (int i = 0; i < strlen(reading); i++)
                    {
                        if (reading[i] == ',')
                        {
                            temp = atoi(reading + i + 1);
                            inCount++;
                        }
                        if (inCount == 3)
                        {
                            numSatellites = temp;
                            break;
                        }
                    }
                    Serial.print("#Satellites = ");
                    Serial.println(numSatellites);
                    return true;
                }
            }
            break;
        }
    }
    if (!found)
    {
        Serial.println("Can't find the NMEA sentence of satellites");
        return false;
    }
}