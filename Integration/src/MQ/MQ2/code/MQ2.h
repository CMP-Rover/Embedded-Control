/// Class for the MQ2 gas sensor.
///
/// This sensor detects gas concentration and relays the concentration
/// via the analog pin. If the concentration is past a certain value
/// (configured via the potentiometer on the back), it pulls the digital pin
/// to HIGH, otherwise, it's low.
/// @note For more info: https://lastminuteengineers.com/mq2-gas-senser-arduino-tutorial/

#define MIN_PPM_MQ2 300 ///< minimum gas concentration that can be detected by the sensor
#define MAX_PPM_MQ2 10000 ///< minimum gas concentration that can be detected by the sensor
#define analogVmin 0
#define analogVmax 1023


class MQ2
{
private:
    int analogPin = 0;       ///< This pin should return the gas concentration
    
    int digitalPin = 7;      ///< This pin should be HIGH if a gas is past the configured concentration or LOW if not.
    int WarmupPeroid = 1000; ///< Required so the filliment warms up in ms
    int currentThreshold;
    bool gasDetected = false;
public:
    float Reading;
    /// The constructor for the MQ2 sensor object.
    /// @param analog The analog pin the sensor is connected to
    /// @param digital The digital pin the sensor is connected to
    /// @param reading The reading interval in ms

    MQ2(int analog, int warmup, int Threshold);

    /// Normal destructor, nothing special here.
    ~MQ2();

    /// Reads the gas concentration off the analog pin specified in the constructor.
    /// @warning Since I can't find a proteus library with a 4 pin connector
    /// this hasn't been tested as much as I'd like. Using a sine generator as
    /// a replacement doesn't seem to work well...
    /// @param realConc specifies whether the function should return the mapped concentration
    /// or should return the analog value it reads. (For debugging/testing)
    /// @returns The gas concentration in ppm.
    float GetGasConcentration(bool realConc);

    /// Reads the digital pin specified in the constructor.
    /// @attention This function sets the digital pin's mode to INPUT.
    /// @returns Wether the gas concentration passed the allowed threshold.
    bool IsGasDetected();

    /// Prints the detected gas concentration and whether that concentration is
    /// past the allowed threshold.
    /// @param plotter If false, prints normal info regarding the analog reading and whether gas is detected.
    /// Otherwise, only prints the analog reading for the plotter.
    void PrintMQ2Data(bool plotter);

    /// Waits WarmupPeriod seconds before letting the code continue
    /// Required so that the sensor gets enough time to heat up to detect
    /// concentrations accurately.
    /// @attention This function should be called in setup only since it stops
    /// execution.
    void Warmup();


    void LowSensitivity();
    void MediumSensitivity();
    void HighSesnitivity();
};
