#define MIN_PPM1 10
#define MAX_PPM1 500
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
    MQ7(int analog, int digital, int warmup);
    int GetGasConcentration();
    bool IsGasDetected();
    void PrintMQ7Data();
    void Warmup();
    ~MQ7();
};
