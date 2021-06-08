#include "../Util/Util.h"
#include "../BMP/BMP180.h"
#include "../GPS/GPS.h"
#include "../MQ7/MQ7.h"
#include "../MQ2/MQ2.h"
#include "../DHT/DHT.h"

class Sensors
{
public:
    int gps_pin_rx; // garbage
    int gps_pin_tx;
    int mq7_digital;
    int mq7_analog;
    int mq2_digital;
    int mq2_analog;
    int dht_pin;
    GPS *gps;
    double latitude;
    double longitude;
    MQ7 *mq7;
    int MQ7_Conc;
    DHT *dht;
    int DHT_rh;
    int DHT_Temperature;
    MQ2 *mq2;
    int MQ2_Conc;
    //SoftwareSerial* gpsSerial;

    Sensors(int gps_pin_tx_c, int gps_pin_rx_c, int mq7_analog_c, int mq2_analog_c, int dht_pin_c)
    {
        gps_pin_rx = gps_pin_rx_c; // garbage
        gps_pin_tx = gps_pin_tx_c;
        mq7_digital = mq7_analog_c;
        mq7_analog = mq7_analog_c;
        mq2_digital = mq2_analog_c;
        mq2_analog = mq2_analog_c;
        dht_pin = dht_pin_c;
        //SoftwareSerial gpsSerial(gps_pin_tx_c, gps_pin_rx_c);
        //gpss = & gpsSerial;
        //gpsSerial = gpss;

        //SoftwareSerial gpsSerial (gps_pin_tx, gps_pin_rx_c);

        /////////////////////////////////////////////////////initializing gps and reading initial data/////////////////
        gps = new GPS(gps_pin_tx_c, gps_pin_rx_c);

        //while(!(gps->DebugSatellites())){}
        gps->readData(500);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        mq7 = new MQ7(mq7_analog, 1000, Low);
        //mq7->Warmup();
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        dht = new DHT(dht_pin);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        mq2 = new MQ2(mq2_analog, 2000, Low);
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }

    // TODO Finish this
    String GetCurrentGPSLocation()
    {
        return (gps->getPosition());
    }
    bool readGPS(bool request)
    {
        if (request)
        {
            gps->readData(500);
            latitude = gps->getLatitude();
            longitude = gps->getLongitude();
        }
    }
    void PrintGPSData()
    {
        Serial.println(GetCurrentGPSLocation()); //ROS
    }

    void readMQ7()
    {
        mq7->PrintMQ7Data(true);
        MQ7_Conc = mq7->analog_value;
    }

    void readDHT()
    {
        dht->Read_data();
        if (dht->get_temperature() < 100)
        {
            DHT_rh = dht->get_RH();
            DHT_Temperature = dht->get_temperature();
        }
    }

    void readMQ2()
    {
        mq2->PrintMQ2Data(false);
        MQ2_Conc = mq2->Reading;
    }
};