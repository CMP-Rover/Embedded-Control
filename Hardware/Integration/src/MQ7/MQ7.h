/// Class for MQ7 gas sensor.
///
/// This sensor detects the Carbon monoxide concentration and outputs it as a voltage signal from the analog pin. If the concentration is past a certain value
/// (configured via the potentiometer on the back), it pulls the digital pin
/// it has a range of 10 -> 500 ppm (parts per million)
///

// NOTE: MQ7 should be used with (60s,5v) and (90s, 1.4v) cycles
// The 5v period is to clean the sensor and the 1.4v is to read concentrations
// The sensor will still respond to changes in CO (if you breath on it for example) but will not be accurate with respect to concentration


#define MIN_PPM_MQ7  10
#define MAX_PPM_MQ7  500
#define WARMUP_PERIOD  1000 //meliseconds
#define ANALOG_PIN  0
#define DIGITAL_PIN  2
#define MAX_OUTPUT  4.3
#define MIN_OUTPUT  2.5


class MQ7
{
private:
    int analog_pin;
    int digital_pin;
    int warmup_period;
    
    int detectionThreshold;
    bool gasDetected;

public:
    int analog_value;
    /// The constructer for the MQ7 sensor object.
    /// @param analog the analog pin the sensor is connected to
    /// @param digital the digital pin the sensor is conneced to
    /// @param warmup the warmup period the sensor needs before it can work
    MQ7(int analog, int warmup, int threshold);

    /// Reads the Carbon Monoxide concentration from the analog pin specified in the constructor.
    /// The sensor sends a voltage representing the CO concentration
    ///
    /// @param mapToPPM determines whether to map the analog values to PPM or just return the analog value as is.
    /// @param threshold determines the analog reading at which the code sets gasDetected to true, also determines whether the function returns 0 or th reading.
    /// Knowing the minimum and maximum range of CO that it can measure in ppm and knowing the minimum and maximum output voltage correspodning to those concentrations,
    /// we can use cross multiplication to get the result
    ///
    /// 4.3v (max voltage) --> 500 ppm (max CO concentration)
    ///
    /// Vout (voltage measured from the device) ---> ??? ppm
    ///
    /// @returns the Carbon Monoxide concentration in ppm
    void GetGasConcentration(float &, float &, bool mapToPPM);

    /// Reads the digital pin of the sensor
    /// This will be true if the Carbon Monoxide concentration has exceeded a certain limit
    /// The threshold level can be changed using a potentiometer
    /// @returns a boolean that signifies whether the CO concentration has exceeded the limit or not
    bool IsGasDetected();

    /// Prints the Carbon Monoxide concentration
    /// @param plotter If false, prints normal info regarding the analog reading and whether gas is detected.
    /// Otherwise, only prints the analog reading for the plotter.
    void PrintMQ7Data(bool plotter);

    /// This function just acts as a delay so that the sensor can heat up
    /// This is necessary for the sensor to function in real life
    /// @attention The warmpup duration is currently set to one second but it should be changed when working with the sensor for real
    /// This function is only called once for setup
    void Warmup();

    /// MQ7 class destructor
    ~MQ7();
};
