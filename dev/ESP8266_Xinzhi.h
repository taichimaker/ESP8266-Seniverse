#ifndef _ESP8266_Xinzhi_H_
#define _ESP8266_Xinzhi_H_
 
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

class WeatherNow {
  public:
    WeatherNow();

    void config(String userKey, String location, String unit);
    
  private:
    WiFiClient _wifiClient; 
   
    const char* _host = "api.seniverse.com";     // 服务器地址  
    const int _httpPort = 80;                    // 服务器端口
        
    String _reqUserKey;   // 私钥
    String _reqLocation;  // 城市
    String _reqUnit;      // 摄氏/华氏
};
 
#endif
