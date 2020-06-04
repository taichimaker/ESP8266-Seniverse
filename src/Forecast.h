#ifndef _FORECAST_H_
#define _FORECAST_H_
 
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

#define DEBUG   // 调试用宏定义

// 获取天气预报信息类
class Forecast {
  public:
    Forecast();

    void config(String userKey, String location, String unit);
    bool update();
    String getDayText(int index);
    int getDayCode(int index);
    String getNightText(int index);
    int getNightCode(int index);    
    int getHigh(int index); 
    int getLow(int index); 

    float getRain(int index);          // 获取降水概率信息
    String getWindDirection(int index);// 获取风向信息
    float getWindSpeed(int index);     // 获取风速信息
    int getWindScale(int index);       // 获取风力信息
    int getHumidity(int index);        // 获取湿度信息
       
    String getLastUpdate();            // 获取心知天气信息更新时间
    String getServerCode();            // 获取服务器响应状态码
   
  private:  
    const char* _host = "api.seniverse.com";     // 服务器地址  
        
    String _reqUserKey;   // 私钥
    String _reqLocation;  // 城市
    String _reqUnit;      // 摄氏/华氏
        
    String _response_code =  "no_init";   // 服务器响应状态码 

    void _parseForecastInfo(WiFiClient client);      // 解析实时天气信息信息
    
    String  _text_day[3] = {"no_init", "no_init", "no_init"};   // 白天天气(字符串)
    int _code_day[3] = {999, 999, 999};                         // 白天天气（代码）
    String _text_night[3] = {"no_init", "no_init", "no_init"};  // 晚上天气（字符串）
    int _code_night[3] = {999, 999, 999};      // 晚上天气（代码）
    int _degree_high[3] = {999, 999, 999};     // 最高气温
    int _degree_low[3] = {999, 999, 999};      // 最低气温
    
    float _rainfall[3] = {999, 999, 999};       // 降水概率
    String _wind_direction[3] = {"no_init", "no_init", "no_init"}; // 风向
    float _wind_speed[3] = {999, 999, 999};     // 风速
    int _wind_scale[3] = {999, 999, 999};       // 风力
    int _humidity[3] = {999, 999, 999};         // 湿度
    
    String _last_update;                        // 心知天气信息更新时间    
};
#endif
