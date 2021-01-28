#include <Wire.h> // Library for I2C communication
#include <SPI.h>  // not used here, but needed to prevent a RTClib compile error
#include "RTClib.h"

RTC_DS3231 RTC;     // Setup an instance of DS1307 naming it RTC

void setup () 
{
  Serial.begin(9600); // Set serial port speed
  Wire.begin(); // Start the I2C
  RTC.begin();  // Init RTC
  RTC.adjust(DateTime(__DATE__, __TIME__));  // Time and date is expanded to date and time on your computer at compiletime
  Serial.print('Time and date set');
}

void loop () {
  DateTime now = RTC.now();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
}
