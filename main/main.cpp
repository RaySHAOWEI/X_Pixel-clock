#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <time.h>
volatile int state;

Adafruit_NeoMatrix pixelclock = Adafruit_NeoMatrix(32, 8, 2, NEO_MATRIX_BOTTOM + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE, NEO_GRB + NEO_KHZ800);

#include "Typeface.h"

void SmartConfig()
{
  WiFi.mode(WIFI_STA);
  Serial.println("\r\nWait for Smartconfig...");
  WiFi.beginSmartConfig();
  while (1)
  {
    pixelclock.fillScreen(0);
    pixelclock.setBrightness(100);
    print_str(3, 1, "Hotspot", 0x37E6); //显示“Hotspot” 动画：常亮 0x37E6
    pixelclock.show();
    delay(1000);

    if (WiFi.smartConfigDone())
    {
      Serial.println("SmartConfig Success");
      Serial.printf("SSID:%s", WiFi.SSID().c_str());
      Serial.printf(",PSW:%s\r\n", WiFi.psk().c_str());
      break;
    }
  }
}

bool AutoConfig()
{
  WiFi.begin();
  for (int i = 0; i < 5; i++)
  { //尝试配网5次
    if (WiFi.status() == WL_CONNECTED)
    {
      Serial.println("WIFI SmartConfig Success");
      Serial.printf("SSID:%s", WiFi.SSID().c_str());
      Serial.printf(",PSW:%s\r\n", WiFi.psk().c_str());
      Serial.print("LocalIP:");
      Serial.print(WiFi.localIP());
      Serial.print(" ,GateIP:");
      Serial.println(WiFi.gatewayIP());
      return true;
    }
    else
    {
      pixelclock.fillScreen(0);
      pixelclock.setBrightness(100);
      print_str(4, 1, "WiFi", 0xFFFF); //显示“WIFI”，动画：常亮 0xFFFF 4 1
      pixelclock.show();
      pixelclock.drawPixel(21, 3, 0x319F);
      pixelclock.show();
      delay(200);
      pixelclock.drawPixel(23, 2, 0x319F);
      pixelclock.drawPixel(23, 4, 0x319F);
      pixelclock.drawPixel(24, 3, 0x319F);
      pixelclock.show();
      delay(300);
      pixelclock.drawPixel(24, 0, 0x319F);
      pixelclock.drawPixel(24, 6, 0x319F);
      pixelclock.drawPixel(25, 1, 0x319F);
      pixelclock.drawPixel(25, 5, 0x319F);
      pixelclock.drawPixel(26, 2, 0x319F);
      pixelclock.drawPixel(26, 4, 0x319F);
      pixelclock.drawPixel(27, 3, 0x319F);
      pixelclock.show();
      delay(400); // WiFi连接动画
    }
  }
  print_str(4, 1, "faild", 0xF800);
  pixelclock.show();
  Serial.println("WIFI AutoConfig Faild!");
  return false;
}

String get_timeY()
{
  time_t now;
  time(&now);
  char time_outputY[30];
  strftime(time_outputY, 30, "%Y", localtime(&now));
  return String(time_outputY);
} //获取年

String get_timeu()
{
  time_t now;
  time(&now);
  char time_outputu[30];
  strftime(time_outputu, 30, "%u", localtime(&now));
  return String(time_outputu);
} //获取星期

String get_timeX()
{
  time_t now;
  time(&now);
  char time_outputX[30];
  strftime(time_outputX, 30, "%X", localtime(&now));
  return String(time_outputX);
} //获取时间串

String get_timem()
{
  time_t now;
  time(&now);
  char time_outputm[30];
  strftime(time_outputm, 30, "%m", localtime(&now));
  return String(time_outputm);
} //获取月

String get_timed()
{
  time_t now;
  time(&now);
  char time_outputd[30];
  strftime(time_outputd, 30, "%d", localtime(&now));
  return String(time_outputd);
} //获取日

String get_timeH(){
  time_t now;
  time(& now);
  char time_outputH[30];
  strftime(time_outputH, 30, "%H", localtime(& now));
  return String(time_outputH);
}

String get_timeM(){
  time_t now;
  time(& now);
  char time_outputM[30];
  strftime(time_outputM, 30, "%M", localtime(& now));
  return String(time_outputM);
}

String get_timeS(){
  time_t now;
  time(& now);
  char time_outputS[30];
  strftime(time_outputS, 30, "%S", localtime(& now));
  return String(time_outputS);
}

void show_Hello()
{
  show_char(4, 1, 'H', 0xFB2C);
  show_char(8, 1, 'e', 0xFCCC);
  show_char(12, 1, 'l', 0xFFEC);
  show_char(16, 1, 'l', 0x67F3);
  show_char(20, 1, 'o', 0x37FF);
  pixelclock.show();
}

void show_week(int x, int y)
{
  pixelclock.drawPixel((x + 3), (y + 7), 0x9CD3);
  pixelclock.drawPixel((x + 4), (y + 7), 0x9CD3);
  pixelclock.drawPixel((x + 5), (y + 7), 0x9CD3);
  pixelclock.drawPixel((x + 7), (y + 7), 0x9CD3);
  pixelclock.drawPixel((x + 8), (y + 7), 0x9CD3);
  pixelclock.drawPixel((x + 9), (y + 7), 0x9CD3);
  pixelclock.drawPixel((x + 11), (y + 7), 0x9CD3);
  pixelclock.drawPixel((x + 12), (y + 7), 0x9CD3);
  pixelclock.drawPixel((x + 13), (y + 7), 0x9CD3);
  pixelclock.drawPixel((x + 15), (y + 7), 0x9CD3);
  pixelclock.drawPixel((x + 16), (y + 7), 0x9CD3);
  pixelclock.drawPixel((x + 17), (y + 7), 0x9CD3);
  pixelclock.drawPixel((x + 19), (y + 7), 0x9CD3);
  pixelclock.drawPixel((x + 20), (y + 7), 0x9CD3);
  pixelclock.drawPixel((x + 21), (y + 7), 0x9CD3);
  pixelclock.drawPixel((x + 23), (y + 7), 0x9CD3);
  pixelclock.drawPixel((x + 24), (y + 7), 0x9CD3);
  pixelclock.drawPixel((x + 25), (y + 7), 0x9CD3);
  pixelclock.drawPixel((x + 27), (y + 7), 0x9CD3);
  pixelclock.drawPixel((x + 28), (y + 7), 0x9CD3);
  pixelclock.drawPixel((x + 29), (y + 7), 0x9CD3);
  switch (String(get_timeu()).toInt())
  {
  case 1:
    pixelclock.drawPixel((x + 3), (y + 7), 0xFFFF);
    pixelclock.drawPixel((x + 4), (y + 7), 0xFFFF);
    pixelclock.drawPixel((x + 5), (y + 7), 0xFFFF);
    break;
  case 2:
    pixelclock.drawPixel((x + 7), (y + 7), 0xFFFF);
    pixelclock.drawPixel((x + 8), (y + 7), 0xFFFF);
    pixelclock.drawPixel((x + 9), (y + 7), 0xFFFF);
    break;
  case 3:
    pixelclock.drawPixel((x + 11), (y + 7), 0xFFFF);
    pixelclock.drawPixel((x + 12), (y + 7), 0xFFFF);
    pixelclock.drawPixel((x + 13), (y + 7), 0xFFFF);
    break;
  case 4:
    pixelclock.drawPixel((x + 15), (y + 7), 0xFFFF);
    pixelclock.drawPixel((x + 16), (y + 7), 0xFFFF);
    pixelclock.drawPixel((x + 17), (y + 7), 0xFFFF);
    break;
  case 5:
    pixelclock.drawPixel((x + 19), (y + 7), 0xFFFF);
    pixelclock.drawPixel((x + 20), (y + 7), 0xFFFF);
    pixelclock.drawPixel((x + 21), (y + 7), 0xFFFF);
    break;
  case 6:
    pixelclock.drawPixel((x + 23), (y + 7), 0xFFFF);
    pixelclock.drawPixel((x + 24), (y + 7), 0xFFFF);
    pixelclock.drawPixel((x + 25), (y + 7), 0xFFFF);
    break;
  case 7:
    pixelclock.drawPixel((x + 27), (y + 7), 0xFFFF);
    pixelclock.drawPixel((x + 28), (y + 7), 0xFFFF);
    pixelclock.drawPixel((x + 29), (y + 7), 0xFFFF);
    break;
  }
}

void show_now_time(int x, int y)
{
  print_str((x + 3), (y + 1), get_timeH(), 0x333F);
  print_str((x + 13), (y + 1), get_timeM(), 0x333F);
  print_str((x + 23), (y + 1), get_timeS(), 0x333F);
  pixelclock.drawPixel((x + 11), (y + 2), 0x333F);
  pixelclock.drawPixel((x + 11), (y + 4), 0x333F);
  pixelclock.drawPixel((x + 21), (y + 2), 0x333F);
  pixelclock.drawPixel((x + 21), (y + 4), 0x333F);
}

void show_date(int x, int y)
{
  print_str((x + 7), (y + 1), get_timem(), 0x333F);
  pixelclock.drawPixel((x + 15), (y + 3), 0x333F);
  pixelclock.drawPixel((x + 16), (y + 3), 0x333F);
  pixelclock.drawPixel((x + 17), (y + 3), 0x333F);
  print_str((x + 19), (y + 1), get_timed(), 0x333F);
}

void setup()
{
  Serial.begin(9600);
  pixelclock.begin();
  if (!AutoConfig())
  {
    SmartConfig();
  }
  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  setenv("TZ", "CST-8", 1);
  show_str(4, 1, "WiFi", 0xFFFF);
  pixelclock.fillScreen(0);
  pixelclock.setBrightness(100);
  show_str(4, 1, "WiFi", 0xFFFF);
  pixelclock.drawPixel(21, 4, 0x37E6);
  pixelclock.show();
  delay(100);
  pixelclock.drawPixel(22, 5, 0x37E6);
  pixelclock.show();
  delay(100);
  pixelclock.drawPixel(23, 6, 0x37E6);
  pixelclock.show();
  delay(100);
  pixelclock.drawPixel(24, 5, 0x37E6);
  pixelclock.show();
  delay(100);
  pixelclock.drawPixel(25, 4, 0x37E6);
  pixelclock.show();
  delay(100);
  pixelclock.drawPixel(26, 3, 0x37E6);
  pixelclock.show();
  delay(100);
  pixelclock.drawPixel(27, 2, 0x37E6);
  pixelclock.show();
  delay(100);
  pixelclock.drawPixel(28, 1, 0x37E6);
  pixelclock.show();
  delay(100);
  bright_slow_down(100); //渐渐消失特效
  do
  {
    pixelclock.fillScreen(0);
    pixelclock.setBrightness(100);
    show_str(4, 1, "Time", 0xFFFF); //显示“Time”，动画：常亮 0xFFFF 4 1
    pixelclock.drawPixel(20, 5, 0xFFFF);
    pixelclock.show();
    delay(300);
    pixelclock.drawPixel(22, 5, 0xFFFF);
    pixelclock.show();
    delay(350);
    pixelclock.drawPixel(24, 5, 0xFFFF);
    pixelclock.show();
    delay(400);
    pixelclock.drawPixel(26, 5, 0xFFFF);
    pixelclock.show();
    delay(450);
    pixelclock.drawPixel(28, 5, 0xFFFF);
    pixelclock.show();
    delay(500);
    pixelclock.drawPixel(30, 5, 0xFFFF);
    pixelclock.show();
    delay(550);
  } while ((get_timeY() == "1970"));
  pixelclock.fillScreen(0);
  pixelclock.setBrightness(100);
  show_str(4, 1, "Time", 0xFFFF); //显示“Time”，动画：常亮 0xFFFF 4 1
  pixelclock.drawPixel(21, 4, 0x37E6);
  pixelclock.show();
  delay(100);
  pixelclock.drawPixel(22, 5, 0x37E6);
  pixelclock.show();
  delay(100);
  pixelclock.drawPixel(23, 6, 0x37E6);
  pixelclock.show();
  delay(100);
  pixelclock.drawPixel(24, 5, 0x37E6);
  pixelclock.show();
  delay(100);
  pixelclock.drawPixel(25, 4, 0x37E6);
  pixelclock.show();
  delay(100);
  pixelclock.drawPixel(26, 3, 0x37E6);
  pixelclock.show();
  delay(100);
  pixelclock.drawPixel(27, 2, 0x37E6);
  pixelclock.show();
  delay(100);
  pixelclock.drawPixel(28, 1, 0x37E6);
  pixelclock.show();
  delay(100);
  bright_slow_down(100); //渐渐消失特效
  pixelclock.fillScreen(0);
  for (int i = 0; i <= 100; i = i + (1))
  {
    pixelclock.setBrightness(i);
    show_Hello();
    pixelclock.drawPixel(25, 1, 0x9CDF);
    pixelclock.drawPixel(25, 2, 0x9CDF);
    pixelclock.drawPixel(25, 3, 0x9CDF);
    pixelclock.drawPixel(25, 4, 0x9CDF);
    pixelclock.drawPixel(25, 6, 0x9CDF);
    pixelclock.show();
    delay(5);
  }
  bright_slow_down(100); //渐渐消失特效
  pixelclock.fillScreen(0);
  for (int i = 0; i <= 50; i = i + (1))
  {
    pixelclock.setBrightness(i);
    pixelclock.fillScreen(0);
    show_now_time(0, 0);
    show_week(0, 0);
    pixelclock.show();
    delay(5);
  }
  state = 1;
  pinMode(13, INPUT);
  pinMode(15, INPUT);
}

void loop()
{
  pixelclock.setBrightness(50);
  if (digitalRead(13))
  {
    if (state == 1)
    {
      for (int i = 0; i <= 32; i = i + (1))
      {
        pixelclock.fillScreen(0);
        show_now_time(i, 0);
        show_date(i - 32, 0);
        show_week(0, 0);
        pixelclock.show();
        delay(5);
      }
      state = 2;
    }
    else if (state == 2)
    {
      for (int i = 0; i <= 32; i = i + (1))
      {
        pixelclock.fillScreen(0);
        show_now_time(i - 32, 0);
        show_date(i, 0);
        show_week(0, 0);
        pixelclock.show();
        delay(5);
      }
      state = 1;
    }
  }
  if (digitalRead(15))
  {
    if (state == 1)
    {
      for (int i = 32; i >= 0; i = i + (-1))
      {
        pixelclock.fillScreen(0);
        show_now_time(i - 32, 0);
        show_date(i, 0);
        show_week(0, 0);
        pixelclock.show();
        delay(5);
      }
      state = 2;
    }
    else if (state == 2)
    {
      for (int i = 32; i >= 0; i = i + (-1))
      {
        pixelclock.fillScreen(0);
        show_now_time(i, 0);
        show_date(i - 32, 0);
        show_week(0, 0);
        pixelclock.show();
        delay(5);
      }
      state = 1;
    }
  }
  if (state == 1)
  {
    pixelclock.fillScreen(0);
    show_now_time(0, 0);
    show_week(0, 0);
    pixelclock.show();
  }
  if (state == 2)
  {
    pixelclock.fillScreen(0);
    show_date(0, 0);
    show_week(0, 0);
    pixelclock.show();
  }
}