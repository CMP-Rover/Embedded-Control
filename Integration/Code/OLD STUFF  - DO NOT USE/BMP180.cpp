
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#ifdef __AVR_ATtiny85__
#include "TinyWireM.h"
#define Wire TinyWireM
#else
#include <Wire.h>
#endif

#include <limits.h>
#include <math.h>

#include "BMP180.h"

static bmp180_calib_data
    _bmp180_coeffs; // Last read accelerometer data will be available here
static uint8_t _bmp180Mode;

/*
 PRIVATE FUNCTIONS
 ***************************************************************************/

/**************************************************************************/
/*!
    @brief  Writes an 8 bit value over I2C
*/
/**************************************************************************/
static void writeCommand(byte reg, byte value) {
  Wire.beginTransmission((uint8_t)BMP_ADDRESS);
#if ARDUINO >= 100
  Wire.write((uint8_t)reg);
  Wire.write((uint8_t)value);
#else
  Wire.send(reg);
  Wire.send(value);
#endif
  Wire.endTransmission();
}

/**************************************************************************/
/*!
    @brief  Reads an 8 bit value over I2C
*/
/**************************************************************************/
static void read8(byte reg, uint8_t *value) {
  Wire.beginTransmission((uint8_t)BMP_ADDRESS);
#if ARDUINO >= 100
  Wire.write((uint8_t)reg);
#else
  Wire.send(reg);
#endif
  Wire.endTransmission();
  Wire.requestFrom((uint8_t)BMP_ADDRESS, (byte)1);
#if ARDUINO >= 100
  *value = Wire.read();
#else
  *value = Wire.receive();
#endif
  Wire.endTransmission();
}

/**************************************************************************/
/*!
    @brief  Reads a 16 bit value over I2C
*/
/**************************************************************************/
static void read16(byte reg, uint16_t *value) {
  Wire.beginTransmission((uint8_t)BMP_ADDRESS);
#if ARDUINO >= 100
  Wire.write((uint8_t)reg);
#else
  Wire.send(reg);
#endif
  Wire.endTransmission();
  Wire.requestFrom((uint8_t)BMP_ADDRESS, (byte)2);
#if ARDUINO >= 100
  *value = (Wire.read() << 8) | Wire.read();
#else
  *value = (Wire.receive() << 8) | Wire.receive();
#endif
  Wire.endTransmission();
}

/**************************************************************************/
/*!
    @brief  Reads a signed 16 bit value over I2C
*/
/**************************************************************************/
static void readS16(byte reg, int16_t *value) {
  uint16_t i;
  read16(reg, &i);
  *value = (int16_t)i;
}

/**************************************************************************/
/*!
    @brief  Reads the factory-set coefficients
*/
/**************************************************************************/
static void readCoefficients(void) {

  readS16(BMP180_REGISTER_CAL_AC1, &_bmp180_coeffs.ac1);
  readS16(BMP180_REGISTER_CAL_AC2, &_bmp180_coeffs.ac2);
  readS16(BMP180_REGISTER_CAL_AC3, &_bmp180_coeffs.ac3);
  read16(BMP180_REGISTER_CAL_AC4, &_bmp180_coeffs.ac4);
  read16(BMP180_REGISTER_CAL_AC5, &_bmp180_coeffs.ac5);
  read16(BMP180_REGISTER_CAL_AC6, &_bmp180_coeffs.ac6);
  readS16(BMP180_REGISTER_CAL_B1, &_bmp180_coeffs.b1);
  readS16(BMP180_REGISTER_CAL_B2, &_bmp180_coeffs.b2);
  readS16(BMP180_REGISTER_CAL_MB, &_bmp180_coeffs.mb);
  readS16(BMP180_REGISTER_CAL_MC, &_bmp180_coeffs.mc);
  readS16(BMP180_REGISTER_CAL_MD, &_bmp180_coeffs.md);

}
/**************************************************************************/
static void readRawTemperature(int32_t *temperature) {

  uint16_t t;
  writeCommand(BMP180_REGISTER_CONTROL, BMP180_REGISTER_READTEMPCMD);
  delay(5);
  read16(BMP180_REGISTER_TEMPDATA, &t);
  *temperature = t;

}

/**************************************************************************/
static void readRawPressure(int32_t *pressure) {

  uint8_t p8;
  uint16_t p16;
  int32_t p32;

  writeCommand(BMP180_REGISTER_CONTROL,
               BMP180_REGISTER_READPRESSURECMD + (_bmp180Mode << 6));
  switch (_bmp180Mode) {
  case BMP180_MODE_ULTRALOWPOWER:
    delay(5);
    break;
  case BMP180_MODE_STANDARD:
    delay(8);
    break;
  case BMP180_MODE_HIGHRES:
    delay(14);
    break;
  case BMP180_MODE_ULTRAHIGHRES:
  default:
    delay(26);
    break;
  }

  read16(BMP180_REGISTER_PRESSUREDATA, &p16);
  p32 = (uint32_t)p16 << 8;
  read8(BMP180_REGISTER_PRESSUREDATA + 2, &p8);
  p32 += p8;
  p32 >>= (8 - _bmp180Mode);

  *pressure = p32;

}

/**************************************************************************/
/*!
    @brief  Compute B5 coefficient used in temperature & pressure calcs.
*/
/**************************************************************************/
int32_t _BMP180_::computeB5(int32_t ut) {
  int32_t X1 =
      (ut - (int32_t)_bmp180_coeffs.ac6) * ((int32_t)_bmp180_coeffs.ac5) >> 15;
  int32_t X2 =
      ((int32_t)_bmp180_coeffs.mc << 11) / (X1 + (int32_t)_bmp180_coeffs.md);
  return X1 + X2;
}

/***************************************************************************
 PUBLIC FUNCTIONS
 ***************************************************************************/

/**************************************************************************/
/*!
    @brief  Setups the HW
*/
/**************************************************************************/
bool _BMP180_::begin(bmp180_mode_t mode) {
  // Enable I2C
  Wire.begin();

  /* Mode boundary check */
  
  if ((mode > BMP180_MODE_ULTRAHIGHRES) || (mode < 0)) {
    mode = BMP180_MODE_ULTRAHIGHRES;
  }

  /* Make sure we have the right device */
  uint8_t id;
  read8(BMP180_REGISTER_CHIPID, &id);
  if (id != 0x55) {
    return false;
  }
  
  /* Set the mode indicator */
  _bmp180Mode = 0;

  /* Coefficients need to be read once */
  readCoefficients();

  return true;
}

/**************************************************************************/
/*!
    @brief  Gets the compensated pressure level in kPa
*/
/**************************************************************************/
void _BMP180_::getPressure(float *pressure) {
  int32_t ut = 0, up = 0, compp = 0;
  int32_t x1, x2, b5, b6, x3, b3, p;
  uint32_t b4, b7;

  /* Get the raw pressure and temperature values */
  readRawTemperature(&ut);
  readRawPressure(&up);

  /* Temperature compensation */
  b5 = computeB5(ut);

  /* Pressure compensation */
  b6 = b5 - 4000;
  x1 = (_bmp180_coeffs.b2 * ((b6 * b6) >> 12)) >> 11;
  x2 = (_bmp180_coeffs.ac2 * b6) >> 11;
  x3 = x1 + x2;
  b3 = (((((int32_t)_bmp180_coeffs.ac1) * 4 + x3) << _bmp180Mode) + 2) >> 2;
  x1 = (_bmp180_coeffs.ac3 * b6) >> 13;
  x2 = (_bmp180_coeffs.b1 * ((b6 * b6) >> 12)) >> 16;
  x3 = ((x1 + x2) + 2) >> 2;
  b4 = (_bmp180_coeffs.ac4 * (uint32_t)(x3 + 32768)) >> 15;
  b7 = ((uint32_t)(up - b3) * (50000 >> _bmp180Mode));

  if (b7 < 0x80000000) {
    p = (b7 << 1) / b4;
  } else {
    p = (b7 / b4) << 1;
  }

  x1 = (p >> 8) * (p >> 8);
  x1 = (x1 * 3038) >> 16;
  x2 = (-7357 * p) >> 16;
  compp = p + ((x1 + x2 + 3791) >> 4);

  /* Assign compensated pressure value */
  *pressure = compp;
}

/**************************************************************************/
/*!
    @brief  Reads the temperatures in degrees Celsius
*/
/**************************************************************************/
void _BMP180_::getTemperature(float *temp) {
  int32_t UT, B5; // following ds convention
  float t;

  readRawTemperature(&UT);

  B5 = computeB5(UT);
  t = (B5 + 8) >> 4;
  t /= 10;

  *temp = t;
}

/**************************************************************************/
/*!
    @brief  Calculates the altitude (in meters) from the specified atmospheric pressure (in hPa), and sea-level pressure (in hPa).
*/
/**************************************************************************/
float _BMP180_::pressureToAltitude(float seaLevel, float atmospheric)
{

	return 44330.0 * (1.0 - pow(atmospheric / seaLevel, 1.0 / 5.255));
}

/**************************************************************************/
/*!
    @brief  Calculates the pressure at sea level (in hPa) from the specified altitude (in meters), and atmospheric pressure (in hPa).
*/
/**************************************************************************/
float _BMP180_::seaLevelForAltitude(float altitude, float atmospheric)
{

	return atmospheric / pow(1.0 - altitude / 44330, 5.255);
}

/**************************************************************************/
