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

#ifndef STASSID
#define STASSID "emmmmm"
#define STAPSK  "xsw123456"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);
bool LED_Flag = false;
String str = 
"<!DOCTYPE html><html><head><meta charset=\"UTF-8\"><meta name=\"viewport\"content=\"width=device-width, initial-scale=1.0\"><meta http-equiv=\"X-UA-Compatible\"content=\"ie=edge\"><title>不知名up的ESP8266网页配网</title></head><body><form name=\"my\">WiFi名称：<input type=\"text\"name=\"s\"placeholder=\"请输入您WiFi的名称\"id=\"aa\"><br>WiFi密码：<input type=\"text\"name=\"p\"placeholder=\"请输入您WiFi的密码\"id=\"bb\"><br><input type=\"button\"value=\"连接\"onclick=\"wifi()\"></form><script language=\"javascript\">function wifi(){var ssid=my.s.value;var password=bb.value;var xmlhttp=new XMLHttpRequest();xmlhttp.open(\"GET\",\"/HandleVal?ssid=\"+ssid+\"&password=\"+password,true);xmlhttp.send()}</script></body></html>";
/*****************************************************
 * 函数名称：handleRoot()
 * 函数说明：客户端请求回调函数
 * 参数说明：无
******************************************************/
void handleRoot() {
  server.send(200, "text/html", str);
}
/*****************************************************
 * 函数名称：HandleVal()
 * 函数说明：对客户端请求返回值处理
 * 参数说明：无
******************************************************/
void HandleVal()
{
    String wifis = server.arg("ssid"); //从JavaScript发送的数据中找ssid的值
    String wifip = server.arg("password"); //从JavaScript发送的数据中找password的值
    Serial.println(wifis); Serial.println(wifip);
    WiFi.begin(wifis,wifip);
}
/*****************************************************
 * 函数名称：handleNotFound()
 * 函数说明：响应失败函数
 * 参数说明：无
******************************************************/
void handleNotFound() {
  digitalWrite(LED_BUILTIN, 0);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(LED_BUILTIN, 1);
}
/*****************************************************
 * 函数名称：htmlConfig()
 * 函数说明：web配置WiFi函数
 * 参数说明：无
******************************************************/
void htmlConfig()
{
    WiFi.mode(WIFI_AP_STA);//设置模式为AP+STA
    digitalWrite(LED_BUILTIN, LOW);
    WiFi.softAP(ssid, password);
    Serial.println("AP设置完成");
    
    IPAddress myIP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(myIP);
  
    if (MDNS.begin("esp8266")) {
      Serial.println("MDNS responder started");
    }
  
    server.on("/", handleRoot);
    server.on("/HandleVal", HTTP_GET, HandleVal);
    server.onNotFound(handleNotFound);//请求失败回调函数
  
    server.begin();//开启服务器
    Serial.println("HTTP server started");
    while(1)
    {
        server.handleClient();
        MDNS.update();  
        if (WiFi.status() == WL_CONNECTED)
        {
            Serial.println("HtmlConfig Success");
            Serial.printf("SSID:%s\r\n", WiFi.SSID().c_str());
            Serial.printf("PSW:%s\r\n", WiFi.psk().c_str());
            Serial.println("HTML连接成功");
            break;
        }
    }  
}




#define PIN 2
#define mw 32
#define mh 8
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(mw, mh, PIN, NEO_MATRIX_TOP + NEO_MATRIX_LEFT +NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,NEO_GRB + NEO_KHZ800);
#include "shuzixianshi.h"
int xswcount=0;
bool WIFI_Status = true;

void smartConfig()
{
  WiFi.mode(WIFI_STA);
  Serial.println("Wait for Smartconfig...");
  WiFi.beginSmartConfig();
  while (1)
  {
    Serial.print(".");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);  matrix.setTextColor(matrix.Color(255,0,255));
    matrix.setCursor(0,0);
    matrix.fillScreen(0);
    matrix.print(F("Fail!"));
    matrix.show();
    if (WiFi.smartConfigDone())
      {
      Serial.println("SmartConfig Success");
      Serial.printf("SSID:%s", WiFi.SSID().c_str());
      Serial.println("");
      Serial.printf("PSW:%s", WiFi.psk().c_str());
      digitalWrite(LED_BUILTIN, LOW);  
      matrix.setTextColor(matrix.Color(255,0,255));
      matrix.setCursor(0,0);
      matrix.fillScreen(0);
      matrix.print(F("Done!"));
      matrix.show();
      break;
      }
  }
}



void setup(){
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(20);
  delay(10);
  pinMode(LED_BUILTIN, OUTPUT);
  for (int i = 1; i <= 10; i = i + (1))
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  digitalWrite(LED_BUILTIN, LOW);
  delay(100);
};
  Serial.begin(9600);
  delay(10);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("正在连接");
  while(WiFi.status()!=WL_CONNECTED)
  {
    if(WIFI_Status)
    {
      Serial.print(".");
      digitalWrite(LED_BUILTIN, HIGH);
      delay(500);
      digitalWrite(LED_BUILTIN, LOW);
      delay(500);  
      matrix.setTextColor(matrix.Color(255,0,255));
      matrix.setCursor(0,0);
      matrix.fillScreen(0);
      matrix.print(F("WiFi>"));
      matrix.show();
      xswcount++;
      if(xswcount>=10)//10s
      {
        WIFI_Status = false;
        Serial.println("WiFi连接失败，请用手机进行配网");   
        matrix.setTextColor(matrix.Color(255,0,255));
        matrix.setCursor(0,0);
        matrix.fillScreen(0);
        matrix.print(F("Fail!"));
        matrix.show();
      }
    }
    else
    {
        WiFi.begin("Ceng Network roll","yzzx30578");
        break;
    }
  }
  Serial.println("连接成功");
  Serial.print("IP:");
  Serial.println(WiFi.localIP());
  digitalWrite(LED_BUILTIN, LOW);  
  matrix.setTextColor(matrix.Color(255,0,255));
  matrix.setCursor(0,0);
  matrix.fillScreen(0);
  matrix.print(F("Done!"));
  matrix.show();
  delay(100);
  NTP.setInterval (600);
  NTP.setNTPTimeout (1500);
  NTP.begin (ntpServer, timeZone, false);
  xswhour = NTP.getTimeHour24();
  xswminute = NTP.getTimeMinute();
  xswsecond = NTP.getTimeSecond();
}

int R = 254;
int n = 1;

void loop(){

  R = R + n;
  if(R >= 255 || R <= 1)
    {
      n = -n;
    }
   
  matrix.fillScreen(0);
  if (String(NTP.getTimeSecond()).toInt() < 10) {
    xswsecond = String("0") + String(NTP.getTimeSecond());
  } 
  else {
    xswsecond = NTP.getTimeSecond();
  }
  if (String(NTP.getTimeMinute()).toInt() < 10) {
    xswminute = String("0") + String(NTP.getTimeMinute());
  } 
  else {
    xswminute = NTP.getTimeMinute();
  }
  if (String(NTP.getTimeHour24()).toInt() < 10) {
    xswhour = String("0") + String(NTP.getTimeHour24());
  } 
  else {
    xswhour = NTP.getTimeHour24();
  }

  prints(String(String(xswhour).substring(0,1)).toInt(),12,matrix.Color(R,0,-R+255));
  prints(String(String(xswhour).substring(1,2)).toInt(),16,matrix.Color(R,0,-R+255));
  prints(String(String(xswminute).substring(0,1)).toInt(),22,matrix.Color(R,0,-R+255));
  prints(String(String(xswminute).substring(1,2)).toInt(),26,matrix.Color(R,0,-R+255));if ((long) (String(xswsecond).toInt()) % (long) (2)) {

    maohao(matrix.Color(R,0,-R+255));
  }

  matrix.show();
}
