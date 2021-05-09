/// Class for DHT11 Temprature and Humidity Sensor.

/// This sensor detects the temperature and relative humidity and outputs it via the output pin. 
/// The output is sent in waves (pulses) so the pin connected to it in the MCU needs to support that.
///
/// The device sends 80 pulses (40 bits in total) each pair of pulses decide whether the bit that's corresponding to them is high or low. 
/// The first 8 bits are the integer part of the temperature, the next 8 are the decimal part. The same follows for the relative humitity.
/// The last 8 bits are the sum of the all the last 32 bits, it's a way to check the validity of the sensor's output. 

#define DATA_PIN 3

class DHT
{
private:
    int data_pin;       ///<  the pin that this device will be connceted to
    unsigned char RH_int, T_int, RH_dec, T_dec, sum;   ///< Temperature and humidity split into their integer and decimal parts. The sum is the sum of the first four values
    unsigned char pulse[80]; ///< the pulses that the MCU will read from the DHT11 sensor that decide whether the bits of the output are high or low
    bool data_correct; ///< A variables to check whether the data is correct or not
public:

	/// The constructor for the DHT11 object.
	///@param data the data pin that the device should be connected to
    DHT(int data);
	
	/// This function does all of the communication between the MCU and the DHT and calculates the temperature and RH from the pulses sent by the DHT.
    void GetData();
	
	/// This function is used to get the integer part of the relative humidity.
	/// @returns The ineger part of the relative humidity as an unsigned character
    unsigned char getRH_int();
	
	/// This function is used to get the decimal part of the relative humidity.
	/// @returns The decimal part of the relative humidity as an unsigned character
	
    unsigned char getRH_dec();
	
	/// This function is used to get the integer part of the temperature.
	/// @returns The ineger part of the temperature as an unsigned character
    unsigned char getT_int();
	
	/// This function is used to get the decimal part of the temperature.
	/// @returns The decimal part of the temperature as an unsigned character
    unsigned char getT_dec();
	
	
	/// Prints the Temperature.
    void printT();
	
	/// Prints the relative humidity.
    void printRH();
	
	/// Checks if a bit is low or high.
	int excpectedPulse(bool lvl);
};

