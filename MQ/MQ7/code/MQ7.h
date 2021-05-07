/// Class for MQ7 gas sensor.
///
/// This sensor detects the Carbon monoxide concentration and outputs it as a voltage signal from the analog pin. If the concentration is past a certain value
/// (configured via the potentiometer on the back), it pulls the digital pin
/// it has a range of 10 -> 500 ppm (parts per million)
/// 
#define MIN_PPM 10
#define MAX_PPM 500
#define WARMUP_PERIOD 1000 //meliseconds
#define ANALOG_PIN 0
#define DIGITAL_PIN 2
#define MAX_OUTPUT 4.3
#define MIN_OUTPUT 2.5

class MQ7
{
private:
    int analog_pin;
    int digital_pin;
    int warmup_period; 
public:
    /// The constructer for the MQ7 sensor object.
    /// @param analog the analog pin the sensor is connected to
    /// @param digital the digital pin the sensor is conneced to
    /// @param warmup the warmup period the sensor needs before it can work
    MQ7(int analog, int digital, int warmup);

    /// Reads the Carbon Monoxide concentration from the analog pin specified in the constructor.
    /// The sensor sends a voltage representing the CO concentration
    ///
    /// Knowing the minimum and maximum range of CO that it can measure in ppm and knowing the minimum and maximum output voltage correspodning to those concentrations, 
    /// we can use cross multiplication to get the result
    ///
    /// 4.3v (max voltage) --> 500 ppm (max CO concentration)
    ///
    /// Vout (voltage measured from the device) ---> ??? ppm
    ///
    /// @returns the Carbon Monoxide concentration in ppm
    int GetGasConcentration();

    /// Reads the digital pin of the sensor
    /// This will be true if the Carbon Monoxide concentration has exceeded a certain limit
    /// The threshold level can be changed using a potentiometer
    /// @returns a boolean that signifies whether the CO concentration has exceeded the limit or not
    bool IsGasDetected();

    /// Prints the Carbon Monoxide concentration
    void PrintMQ7Data();
    
    /// This function just acts as a delay so that the sensor can heat up
    /// This is necessary for the sensor to function in real life
    /// @attention The warmpup duration is currently set to one second but it should be changed when working with the sensor for real
    /// This function is only called once for setup
    void Warmup();

    /// MQ7 class destructor
    ~MQ7();
};
