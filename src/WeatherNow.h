#ifndef _WEATHERNOW_H_
#define _WEATHERNOW_H_
 
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

//#define DEBUG   // 调试用宏定义

// 获取当前天气信息类
class WeatherNow {
  public:
    WeatherNow();

    void config(String userKey, String location, String unit);
    bool update();
    String getWeatherText();
    int getWeatherCode();
    int getDegree();
    String getLastUpdate();
    String getServerCode();
    
  private:  
    const char* _host = "api.seniverse.com";     // 服务器地址  
        
    String _reqUserKey;   // 私钥
    String _reqLocation;  // 城市
    String _reqUnit;      // 摄氏/华氏

    void _parseNowInfo(WiFiClient client);      // 解析实时天气信息信息
    
    String _status_response =  "no_init"; // 服务器响应状态行
    String _response_code =  "no_init";   // 服务器响应状态码
    
    String _now_text_str = "no_init";    
    int _now_code_int = 999; 
    int _now_temperature_int = 999;     
    String _last_update_str = "no_init";   
    
};
#endif
