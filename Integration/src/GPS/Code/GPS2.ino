#include "GPS.h"
GPS G;
void setup()
{
    Serial.begin(9600);
}

void loop()
{

    if (G.readPer())
    {
        G.printAll();//the same as://  Serial.println(G.getPosition());
    }
}
