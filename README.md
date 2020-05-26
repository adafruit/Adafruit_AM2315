# Adafruit AM2315 Humidity + Temp Sensor
[![Build Status](https://github.com/adafruit/Adafruit_AM2315/workflows/Arduino%20Library%20CI/badge.svg)](https://github.com/adafruit/Adafruit_AM2315/actions)[![Documentation](https://github.com/adafruit/ci-arduino/blob/master/assets/doxygen_badge.svg)](http://adafruit.github.io/Adafruit_AM2315/html/index.html)

This is a library for the AM2315 Humidity + Temp sensor

Designed specifically to work with the AM2315 in the Adafruit shop 
  ----> https://www.adafruit.com/products/1293

These sensors use I2C to communicate, 2 pins are required to interface
Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada for Adafruit Industries.  
BSD license, all text above must be included in any redistribution

Check out the links above for our tutorials and wiring diagrams 

To download. click the ZIP button in the top-middle navbar, 
rename the uncompressed folder Adafruit_AM2315. 
Check that the Adafruit_AM2315 folder contains Adafruit_AM2315.cpp and Adafruit_AM2315.h

Place the Adafruit_AM2315 library folder your arduinosketchfolder/libraries/ folder. 
You may need to create the libraries subfolder if its your first library. Restart the IDE.

To connect the AM2315 to the Arduino:

- RED wire goes to +5V
- BLACK wire goes to Ground
- WHITE wire goes to to i2c clock - on '168/'328 Arduino Uno/Duemilanove/etc that's Analog 5
- YELLOW wire goes to i2c data - on '168/'328 Arduino Uno/Duemilanove/etc that's Analog 4

Also see http://arduino.cc/en/Reference/Wire

We also have a great tutorial on Arduino library installation at:
http://learn.adafruit.com/adafruit-all-about-arduino-libraries-install-use
