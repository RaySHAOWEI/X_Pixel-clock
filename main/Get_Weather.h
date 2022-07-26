#include <ArduinoJson.h>
#if defined(ESP32) //ESP32
#include <HTTPClient.h>
#elif defined(ESP8266) //ESP8266
#include <ESP8266HTTPClient.h>
#else
#error "Please check your mode setting,it must be esp8266 or esp32."
#endif

const char *host = "116.62.81.138";        //api.seniverse.com
const char *timeHost = "worldtimeapi.org"; //api.seniverse.com
const uint16_t port = 80;
//===============地区设置===================//

//初始化数据布尔值
unsigned long getTime = 0; //获取网络天气和时间  5s请求一次
bool WeaUp = false;
bool day3Up = false;
bool nowUp = false;
bool airUp = false;
bool lunarUp = false;

//三天天气数据变量
String dayWeatherText[] = {"", "", ""};   //白天天气情况
String nightWeatherText[] = {"", "", ""}; //夜间天气情况
int highTemp[] = {0, 0, 0};               //最高温度
int lowTemp[] = {0, 0, 0};                //最低温度
int windScale[] = {0, 0, 0};              //风力等级
int daysHumidity[] = {0, 0, 0};           //湿度
int daysPrecip[] = {0, 0, 0};             //降雨概率

//实时天气预报变量
int nowTemp;       //当前温度
String nowWeather; //当前天气
int nowFeelsLikes; //当前体感温度
int nowHumidity;   //当前湿度
int nowWindScale;  //当前风力等级

//空气质量变量
int airAqi;
int airPm25;
String airQuality;

//农历数据变量
String lunarZodiac;    //生肖
int lunarMonth;        //农历月
int lunarDay;          //农历日
String lunarMonthName; //农历月中文名
String lunarDayName;   //农历日中文名
String lunarFestival;  //农历节日
String lunarSolarTerm; //二十四节气

int nowDayOfWeek;

// 天气获取数组

//请求URL
String day3Url = "/v3/weather/daily.json?key=" + My_Key + "&location=" + City + "&language=zh-Hans&unit=c&start=0&days=3";
String nowUrl = "/v3/weather/now.json?key=" + My_Key + "&location=" + City + "&language=zh-Hans&unit=c";
String airUrl = "/v3/air/now.json?key=" + My_Key + "&location=" + City + "&language=zh-Hans&scope=city";
String lunarUrl = "/v3/life/chinese_calendar.json?key=" + My_Key + "&start=0&days=1";

String day3HttpRequest = String("GET ") + day3Url + " HTTP/1.1\r\n" +
                         "Host: " + host + "\r\n" +
                         "Connection: close\r\n\r\n";
String nowHttpRequest = String("GET ") + nowUrl + " HTTP/1.1\r\n" +
                        "Host: " + host + "\r\n" +
                        "Connection: close\r\n\r\n";
String airHttpRequest = String("GET ") + airUrl + " HTTP/1.1\r\n" +
                        "Host: " + host + "\r\n" +
                        "Connection: close\r\n\r\n";
String lunarHttpRequest = String("GET ") + lunarUrl + " HTTP/1.1\r\n" +
                          "Host: " + host + "\r\n" +
                          "Connection: close\r\n\r\n";

//请求数据


WiFiClient client;

/**************************************************
 * 函数名称：processMessage
 * 函数功能：将json数据取出
 * 参数说明：无
**************************************************/

void day3processMessage(WiFiClient httpClient)
{

    DynamicJsonDocument doc(1536);

    DeserializationError error = deserializeJson(doc, httpClient);

    if (error)
    {
        Serial.print(F("deserializeJson1() failed: "));
        Serial.println(error.f_str());
        return;
    }

    JsonObject results_0 = doc["results"][0];

    JsonObject results_0_location = results_0["location"];
    const char *results_0_location_id = results_0_location["id"];                           // "WSKM4Q76FR2E"
    const char *results_0_location_name = results_0_location["name"];                       // "晋江"
    const char *results_0_location_country = results_0_location["country"];                 // "CN"
    const char *results_0_location_path = results_0_location["path"];                       // "晋江,泉州,福建,中国"
    const char *results_0_location_timezone = results_0_location["timezone"];               // "Asia/Shanghai"
    const char *results_0_location_timezone_offset = results_0_location["timezone_offset"]; // "+08:00"
    int i = 0;
    for (JsonObject elem : results_0["daily"].as<JsonArray>())
    {

        const char *date = elem["date"];                                   // "2021-07-28", "2021-07-29", "2021-07-30"
        const char *text_day = elem["text_day"];                           // "阴", "阴", "阴"
        const char *code_day = elem["code_day"];                           // "9", "9", "9"
        const char *text_night = elem["text_night"];                       // "阴", "阴", "阴"
        const char *code_night = elem["code_night"];                       // "9", "9", "9"
        const char *high = elem["high"];                                   // "35", "34", "34"
        const char *low = elem["low"];                                     // "27", "27", "27"
        const char *rainfall = elem["rainfall"];                           // "1.2", "1.44", "1.2"
        const char *precip = elem["precip"];                               // "0.32", "0.36", "0.33"
        const char *wind_direction = elem["wind_direction"];               // "南", "南", "南"
        const char *wind_direction_degree = elem["wind_direction_degree"]; // "197", "199", "202"
        const char *wind_speed = elem["wind_speed"];                       // "16.85", "20.3", "19.3"
        const char *wind_scale = elem["wind_scale"];                       // "3", "4", "3"
        const char *humidity = elem["humidity"];                           // "79", "83", "81"
        dayWeatherText[i] = text_day;
        nightWeatherText[i] = text_night;
        highTemp[i] = atoi(high);
        lowTemp[i] = atoi(low);
        windScale[i] = atoi(wind_scale);
        daysHumidity[i] = atoi(humidity);
        daysPrecip[i] = atof(precip) * 100;
        i++;
    }
    day3Up = true;
    const char *results_0_last_update = results_0["last_update"]; // "2021-07-28T20:00:00+08:00"
}

void nowprocessMessage(WiFiClient httpClient)
{
    // Stream& input;

    StaticJsonDocument<768> doc;

    DeserializationError error = deserializeJson(doc, httpClient);

    if (error)
    {
        Serial.print(F("deserializeJson2() failed: "));
        Serial.println(error.f_str());
        return;
    }

    JsonObject results_0 = doc["results"][0];

    JsonObject results_0_location = results_0["location"];
    const char *results_0_location_id = results_0_location["id"];                           // "WSKM4Q76FR2E"
    const char *results_0_location_name = results_0_location["name"];                       // "晋江"
    const char *results_0_location_country = results_0_location["country"];                 // "CN"
    const char *results_0_location_path = results_0_location["path"];                       // "晋江,泉州,福建,中国"
    const char *results_0_location_timezone = results_0_location["timezone"];               // "Asia/Shanghai"
    const char *results_0_location_timezone_offset = results_0_location["timezone_offset"]; // "+08:00"

    JsonObject results_0_now = results_0["now"];
    const char *results_0_now_text = results_0_now["text"];                                   // "阴"
    const char *results_0_now_code = results_0_now["code"];                                   // "9"
    const char *results_0_now_temperature = results_0_now["temperature"];                     // "31"
    const char *results_0_now_feels_like = results_0_now["feels_like"];                       // "30"
    const char *results_0_now_pressure = results_0_now["pressure"];                           // "983"
    const char *results_0_now_humidity = results_0_now["humidity"];                           // "68"
    const char *results_0_now_visibility = results_0_now["visibility"];                       // "30.0"
    const char *results_0_now_wind_direction = results_0_now["wind_direction"];               // "北"
    const char *results_0_now_wind_direction_degree = results_0_now["wind_direction_degree"]; // "0"
    const char *results_0_now_wind_speed = results_0_now["wind_speed"];                       // "15.0"
    const char *results_0_now_wind_scale = results_0_now["wind_scale"];                       // "3"
    const char *results_0_now_clouds = results_0_now["clouds"];                               // "85"
    const char *results_0_now_dew_point = results_0_now["dew_point"];                         // nullptr

    const char *results_0_last_update = results_0["last_update"]; // "2021-07-29T15:24:11+08:00"

    nowTemp = atoi(results_0_now_temperature);        //当前温度
    nowWeather = results_0_now_text;                  //当前天气
    nowFeelsLikes = atoi(results_0_now_feels_like);   //当前体感温度
    nowHumidity = atoi(results_0_now_humidity);       //当前湿度
    nowWindScale = atoi(results_0_now_wind_scale);    //当前风力
    nowUp = true;
}
// 空气质量数据处理
void airprocessMessage(WiFiClient httpClient)
{
    // Stream& input;

    // Stream& input;

    StaticJsonDocument<768> doc;

    DeserializationError error = deserializeJson(doc, httpClient);

    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }

    JsonObject results_0 = doc["results"][0];

    JsonObject results_0_location = results_0["location"];
    const char *results_0_location_id = results_0_location["id"];                           // "WSKM4Q76FR2E"
    const char *results_0_location_name = results_0_location["name"];                       // "晋江"
    const char *results_0_location_country = results_0_location["country"];                 // "CN"
    const char *results_0_location_path = results_0_location["path"];                       // "晋江,泉州,福建,中国"
    const char *results_0_location_timezone = results_0_location["timezone"];               // "Asia/Shanghai"
    const char *results_0_location_timezone_offset = results_0_location["timezone_offset"]; // "+08:00"

    JsonObject results_0_air_city = results_0["air"]["city"];
    const char *results_0_air_city_aqi = results_0_air_city["aqi"];                             // "20"
    const char *results_0_air_city_pm25 = results_0_air_city["pm25"];                           // "6"
    const char *results_0_air_city_pm10 = results_0_air_city["pm10"];                           // "13"
    const char *results_0_air_city_so2 = results_0_air_city["so2"];                             // "2"
    const char *results_0_air_city_no2 = results_0_air_city["no2"];                             // "18"
    const char *results_0_air_city_co = results_0_air_city["co"];                               // "0.520"
    const char *results_0_air_city_o3 = results_0_air_city["o3"];                               // "63"
    const char *results_0_air_city_primary_pollutant = results_0_air_city["primary_pollutant"]; // nullptr
    const char *results_0_air_city_last_update = results_0_air_city["last_update"];
    const char *results_0_air_city_quality = results_0_air_city["quality"]; // "优"

    const char *results_0_last_update = results_0["last_update"]; // "2021-08-02T19:00:00+08:00"
    airAqi = atoi(results_0_air_city_aqi);
    airPm25 = atoi(results_0_air_city_pm25);
    airQuality = results_0_air_city_quality;
    airUp = true;
}
//处理农历JSON
void lunarprocessMessage(WiFiClient httpClient)
{
    // Stream& input;

    StaticJsonDocument<512> doc;

    DeserializationError error = deserializeJson(doc, httpClient);

    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.f_str());
        return;
    }

    JsonObject results_chinese_calendar_0 = doc["results"]["chinese_calendar"][0];
    const char *results_chinese_calendar_0_date = results_chinese_calendar_0["date"];               // "2021-08-02"
    const char *results_chinese_calendar_0_zodiac = results_chinese_calendar_0["zodiac"];           // "牛"
    const char *results_chinese_calendar_0_ganzhi_year = results_chinese_calendar_0["ganzhi_year"]; // "辛丑"
    const char *results_chinese_calendar_0_ganzhi_month = results_chinese_calendar_0["ganzhi_month"];
    const char *results_chinese_calendar_0_ganzhi_day = results_chinese_calendar_0["ganzhi_day"];   // "壬午"
    const char *results_chinese_calendar_0_lunar_year = results_chinese_calendar_0["lunar_year"];   // "2021"
    const char *results_chinese_calendar_0_lunar_month = results_chinese_calendar_0["lunar_month"]; // "6"
    const char *results_chinese_calendar_0_lunar_day = results_chinese_calendar_0["lunar_day"];     // "24"
    const char *results_chinese_calendar_0_lunar_month_name = results_chinese_calendar_0["lunar_month_name"];
    const char *results_chinese_calendar_0_lunar_day_name = results_chinese_calendar_0["lunar_day_name"];
    const char *results_chinese_calendar_0_lunar_leap_month = results_chinese_calendar_0["lunar_leap_month"];
    const char *results_chinese_calendar_0_lunar_festival = results_chinese_calendar_0["lunar_festival"];
    const char *results_chinese_calendar_0_solar_term = results_chinese_calendar_0["solar_term"]; // nullptr

    lunarZodiac = results_chinese_calendar_0_zodiac;              //生肖
    lunarMonth = atoi(results_chinese_calendar_0_lunar_month);    //农历月
    lunarDay = atoi(results_chinese_calendar_0_lunar_day);        //农历日
    lunarMonthName = results_chinese_calendar_0_lunar_month_name; //农历月中文名
    lunarDayName = results_chinese_calendar_0_lunar_day_name;     //农历日中文名
    lunarFestival = results_chinese_calendar_0_lunar_festival;    //农历节日
    lunarSolarTerm = results_chinese_calendar_0_solar_term;       //二十四节气
    lunarUp = true;
}
// HTTP获取当前天气信息
void GET_NowWeather()
{
    if (!client.connect(host, port))
    {
        Serial.println("服务器连接失败");
        return;
    }
    //请求数据
    client.print(nowHttpRequest);
    // 使用find跳过HTTP响应头
    client.find("\r\n\r\n");
    nowprocessMessage(client);
    client.stop();
    if (nowUp == false)
    {
        GET_NowWeather();
    }
}
// HTTP获取三天天气信息
void GET_Day3Weather()
{
    if (!client.connect(host, port))
    {
        Serial.println("服务器连接失败");
        return;
    }
    client.print(day3HttpRequest);
    client.find("\r\n\r\n");
    day3processMessage(client);
    client.stop();
    if (day3Up == false)
    {
        GET_Day3Weather();
    }
}
// HTTP获取空气质量
void GET_AirWeather()
{
    if (!client.connect(host, port))
    {
        Serial.println("服务器连接失败");
        return;
    }
    client.print(airHttpRequest);
    client.find("\r\n\r\n");
    airprocessMessage(client);
    client.stop();
    if (airUp == false)
    {
        GET_Day3Weather();
    }
}
//HTTP获取农历信息
void GET_Lunar()
{
    if (!client.connect(host, port))
    {
        Serial.println("服务器连接失败");
        return;
    }
    client.print(lunarHttpRequest);
    client.find("\r\n\r\n");
    lunarprocessMessage(client);
    client.stop();
    if (lunarUp == false)
    {
        GET_Lunar();
    }
}
/**************************************************
 * 函数名称：GET_Weather
 * 函数功能：http访问获取天气数据
 * 参数说明：无
**************************************************/
void GET_Weather()
{
    if (day3Get)
    {
        GET_Day3Weather();
    }
    if (nowGet)
    {
        GET_NowWeather();
    }
    if (airGet)
    {
        GET_AirWeather();
    }
    if (lunarGet)
    {
        GET_Lunar();
    }

    WeaUp = true;
}

// 处理时间函数
String getTextDay(int day)
{
    return dayWeatherText[day];
} //日间天气
String getTextNight(int day)
{
    return nightWeatherText[day];
} //夜间天气
int getLow(int day)
{
    return highTemp[day];
} //最低温度
int getHigh(int day)
{
    return lowTemp[day];
} //最低温度
int getwindScale(int day)
{
    return windScale[day];
} //风力等级
int gethumidity(int day)
{
    return daysHumidity[day];
} //湿度
int getprecip(int day)
{
    return daysPrecip[day];
} //降雨概率