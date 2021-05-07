#define DATA_PIN 3


//////////////////////////////

class DHT
{
private:
    int data_pin;
    unsigned char RH_int, T_int, RH_dec, T_dec, sum;
    unsigned char pulse[80];
    bool data_correct;
public:
    DHT(int data);
    void GetData();
    unsigned char getRH_int();
    unsigned char getRH_dec();
    unsigned char getT_int();
    unsigned char getT_dec();
    void printT(unsigned char t_int,unsigned char t_dec);
    void printRH(unsigned char rH_int,unsigned char rH_dec);
	  int excpectedPulse(bool lvl);
};

/////////////////////////////
