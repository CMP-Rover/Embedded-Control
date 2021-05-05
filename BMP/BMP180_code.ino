#include"BMP180.h"
_BMP180_ bmpp;
/*BMP180_MODE_ULTRALOWPOWER = 0,
  BMP180_MODE_STANDARD = 1,
  BMP180_MODE_HIGHRES = 2,
  BMP180_MODE_ULTRAHIGHRES = 3
  */
void setup() {
  
  Serial.begin(9600);
 
  bmpp.begin();
  
}

void loop() {
  
  float temp=0,pressure=0,altitude=0;
  bmpp.getTemperature(&temp);
  bmpp.getPressure(&pressure);  //RETURN PRESSURE IN HP (1 HP = 100 PA)
  altitude=bmpp.pressureToAltitude(101325,pressure); //SEALEVEL PRESSURE=101325HP
  Serial.print("Temperature:");
  Serial.println(temp);
  Serial.print("Pressure:");
  Serial.println(pressure/100.0); 
  Serial.print("Altitude:");
  Serial.println(altitude);
  delay(2000);
  
}
