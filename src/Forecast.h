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
    
    String getLastUpdate();
    
  private:  
    const char* _host = "api.seniverse.com";     // 服务器地址  
        
    String _reqUserKey;   // 私钥
    String _reqLocation;  // 城市
    String _reqUnit;      // 摄氏/华氏
    
    String _status_response =  "no_init"; // 服务器响应状态行
    String _response_code =  "no_init";   // 服务器响应状态码 

    void _parseForecastInfo(WiFiClient client);      // 解析实时天气信息信息
    
    String  _text_day[3]; 
    int _code_day[3]; 
    String _text_night[3]; 
    int _code_night[3]; 
    int _degree_high[3];
    int _degree_low[3];
    String _last_update;
    
    /*
    String  _forecast_0_text_day[3]; 
    String  _forecast_0_text_day; 
    int _forecast_0_code_day; 
    String _forecast_0_text_night; 
    int _forecast_0_code_night; 
    int _forecast_0_high;
    int _forecast_0_low;

    String  _forecast_1_text_day; 
    int _forecast_1_code_day; 
    String _forecast_1_text_night; 
    int _forecast_1_code_night; 
    int _forecast_1_high;
    int _forecast_1_low;

    String  _forecast_2_text_day; 
    int _forecast_2_code_day; 
    String _forecast_2_text_night; 
    int _forecast_2_code_night; 
    int _forecast_2_high;
    int _forecast_2_low;
   
    
    */    
};
#endif
