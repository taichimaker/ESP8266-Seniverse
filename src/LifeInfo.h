#ifndef _LIFE_INFO_H_
#define _LIFE_INFO_H_
 
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

//#define DEBUG   // 调试用宏定义

// 获取当前天气信息类
class LifeInfo {
  public:
    LifeInfo();

    void config(String userKey, String location, String unit);
    bool update();
    
    String getCarWash();      // 获取洗车建议
    String getDressing();     // 获取穿衣建议 
    String getFactorFlu();    // 获取流感建议     
    String getExercise();     // 获取运动建议      
    String getTravel();       // 获取旅游建议       
    String getUV();           // 获取紫外线建议        
    String getLastUpdate();   // 返回心知天气信息更新时间  
    String getServerCode();   // 返回服务器响应状态码
        
  private:  
    const char* _host = "api.seniverse.com";     // 服务器地址  
    
    String _status_response =  "no_init"; // 服务器响应状态行
    String _response_code =  "no_init";   // 服务器响应状态码

    void _parseLifeInfo(WiFiClient client);
         
    String _reqUserKey;   // 私钥
    String _reqLocation;  // 城市
    String _reqUnit;      // 摄氏/华氏
    
    String _carWash = "no_init";      // 洗车建议
    String _dressing = "no_init";     // 穿衣建议
    String _factorFlu = "no_init";    // 流感建议    
    String _exercise = "no_init";     // 运动建议    
    String _travel = "no_init";       // 旅游建议    
    String _uv = "no_init";           // 紫外线建议

    String _last_update_str;  // 心知天气信息更新时间
};
#endif
