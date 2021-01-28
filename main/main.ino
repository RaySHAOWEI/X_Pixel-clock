#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <TimeLib.h>
#include <NtpClientLib.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

int8_t timeZone = 8;
const PROGMEM char *ntpServer = "cn.pool.ntp.org";
String xswhour;
String xswminute;
String xswsecond;


#define PIN 2
#define mw 32
#define mh 8

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(mw, mh, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

#include "Typeface.h"

int xswcount=0;
bool WIFI_Status = true;

int R = 255;
int G = 0;
int B = 255;
int light = 20;

void setup() {
  matrix.fillScreen(0);
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(light);
  delay(10);
  //WiFi.begin("Ceng Network roll","yzzx30578");
  WiFi.begin("ChinaNet-5NZCXW","85767651@qq");
  delay(100);
  NTP.setInterval (600);
  NTP.setNTPTimeout (1500);
  NTP.begin (ntpServer, timeZone, false);
  xswhour = NTP.getTimeHour24();
  xswminute = NTP.getTimeMinute();
  xswsecond = NTP.getTimeSecond();
}



void loop() {
  matrix.fillScreen(0);
  
  time_processing();
  
  prints(12, 1, xswhour);
  prints(22, 1, xswminute);
  
  
  if ((long) (xswsecond.toInt()) % (long) (2)) 
  {
    matrix.drawPixel(20, 2, matrix.Color(255, 0, 255));
    matrix.drawPixel(20, 4, matrix.Color(255, 0, 255));
  }

  print_mode(&screen[0][0],1);
  matrix.show();
}

void time_processing()
{
  if (String(NTP.getTimeSecond()).toInt() < 10) 
  {
    xswsecond = String("0") + String(NTP.getTimeSecond());
  } 
  else 
  {
    xswsecond = NTP.getTimeSecond();
  }
  if (String(NTP.getTimeMinute()).toInt() < 10) 
  {
    xswminute = String("0") + String(NTP.getTimeMinute());
  } 
  else 
  {
    xswminute = NTP.getTimeMinute();
  }
  if (String(NTP.getTimeHour24()).toInt() < 10) 
  {
    xswhour = String("0") + String(NTP.getTimeHour24());
  } 
  else 
  {
    xswhour = NTP.getTimeHour24();
  }
}
