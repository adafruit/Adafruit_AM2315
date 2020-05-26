/***************************************************
  This is a library for the AM2315 Humidity & Temp Sensor

  Designed specifically to work with the AM2315 sensor from Adafruit
  ----> https://www.adafruit.com/products/1293

  These displays use I2C to communicate, 2 pins are required to
  interface
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_AM2315.h"
#if defined(__AVR__)
#include <util/delay.h>
#endif

/**************************************************************************/
/*!
    @brief  Instantiates a new AM2320 class
    @param theI2C Optional pointer to a TwoWire object that should be used for
   I2C communication. Defaults to &Wire.
*/
/**************************************************************************/

Adafruit_AM2315::Adafruit_AM2315(TwoWire *theI2C) : _i2c(theI2C) {
  lastreading = 0;
}

/**************************************************************************/
/*!
    @brief  Setups the hardware
    @return True on a successful read, false if first read failed
*/
/**************************************************************************/
boolean Adafruit_AM2315::begin(void) {
  _i2c->begin();

  // try to read data, as a test
  return readData();
}

/**************************************************************************/
/*!
    @brief  Helper to read the temperature & humidity from the device
    @return True if successful data read, note you can only read once every 2
   seconds!
*/
/**************************************************************************/
boolean Adafruit_AM2315::readData(void) {
  uint8_t reply[10];

  if (lastreading) {
    if (millis() > lastreading) {
      if ((millis() - lastreading) <
          2000) {     // has it been less than 2 seconds since?
        return false; // bail, they need to wait longer!
      }
    } else {
      // millis() is less than the last reading, so we wrapped around!
      lastreading = millis();
      return false; // bail again
    }
  }
  lastreading = millis(); // reset our timer

  // Wake up the sensor
  _i2c->beginTransmission(AM2315_I2CADDR);
  delay(2);
  _i2c->endTransmission();

  // OK lets ready!
  _i2c->beginTransmission(AM2315_I2CADDR);
  _i2c->write(AM2315_READREG);
  _i2c->write(0x00); // start at address 0x0
  _i2c->write(4);    // request 4 bytes data
  _i2c->endTransmission();

  delay(10); // add delay between request and actual read!

  _i2c->requestFrom(AM2315_I2CADDR, 8);
  for (uint8_t i = 0; i < 8; i++) {
    reply[i] = _i2c->read();
    // Serial.println(reply[i], HEX);
  }

  if (reply[0] != AM2315_READREG)
    return false;
  if (reply[1] != 4)
    return false; // bytes req'd

  humidity = reply[2];
  humidity *= 256;
  humidity += reply[3];
  humidity /= 10;
  // Serial.print("H"); Serial.println(humidity);

  temp = reply[4] & 0x7F;
  temp *= 256;
  temp += reply[5];
  temp /= 10;
  // Serial.print("T"); Serial.println(temp);

  // change sign
  if (reply[4] >> 7)
    temp = -temp;

  return true;
}

/**************************************************************************/
/*!
    @brief  Read and return the temperature, note you can only read once every 2
   seconds
    @return Floating point Celsius temperature on success, NAN on failure
*/
/**************************************************************************/
float Adafruit_AM2315::readTemperature(void) {
  if (!readData())
    return NAN;
  return temp;
}

/**************************************************************************/
/*!
    @brief  Read and return the humidity, note you can only read once every 2
   seconds
    @return Floating point percentace humidity on success, NAN on failure
*/
/**************************************************************************/
float Adafruit_AM2315::readHumidity(void) {
  if (!readData())
    return NAN;
  return humidity;
}

/**************************************************************************/
/*!
  @brief This method returns both temperature and humidity in a single call and
  using a single I2C request. If you want to obtain both temperature and
  humidity when you sample the sensor, be aware that calling readTemperature()
  and readHumidity() in rapid succession may swamp the sensor and result in
  invalid readingings (the AM2315 manual advisess that continuous samples must
  be at least 2 seconds apart). Calling this method avoids the double I2C
  request.
  @param t Pointer to float to store temperature data in
  @param h Pointer to float to store humidity data in
  @return True if successful data read, note you can only read once every 2
  seconds
 */
bool Adafruit_AM2315::readTemperatureAndHumidity(float *t, float *h) {
  if (!readData())
    return false;

  *t = temp;
  *h = humidity;

  return true;
}

/*********************************************************************/
