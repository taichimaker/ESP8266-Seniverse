#include "ESP8266_Xinzhi.h"
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
 
WeatherNow::WeatherNow(){
}
 
void WeatherNow::config(String userKey, String location, String unit){
  _reqUserKey = userKey; 
  _reqLocation = location;
  _reqUnit = unit;
}

bool WeatherNow::update(){
  WiFiClient _wifiClient;
  
  String reqRes = "/v3/weather/now.json?key=" + _reqUserKey +
                  + "&location=" + _reqLocation + 
                  "&language=en&unit=" +_reqUnit;
                  
  String httpRequest = String("GET ") + reqRes + " HTTP/1.1\r\n" + 
                              "Host: " + _host + "\r\n" + 
                              "Connection: close\r\n\r\n";
                              
  #ifdef DEBUG
  Serial.print("Connecting to ");Serial.println(_host);
  #endif DEBUG
  
  if (_wifiClient.connect(_host, 80)){
    #ifdef DEBUG
    Serial.println(" Success!");
    #endif DEBUG       
 
    // 向服务器发送http请求信息
    _wifiClient.print(httpRequest);
    
    #ifdef DEBUG
    Serial.println("Sending request: ");
    Serial.println(httpRequest); 
    #endif DEBUG        
 
    // 获取并显示服务器响应状态行 
    String status_response = _wifiClient.readStringUntil('\n');
    #ifdef DEBUG
    Serial.print("status_response: ");
    Serial.println(status_response);
    #endif DEBUG   

    // 使用find跳过HTTP响应头
    if (_wifiClient.find("\r\n\r\n")) {
      #ifdef DEBUG
      Serial.println("Found Header End. Start Parsing.");
      #endif DEBUG              
    }

    //String serverPayLoad = _wifiClient.readString();
    //Serial.println(serverPayLoad);
    _parseNowInfo(_wifiClient); 
    _wifiClient.stop();
    return true;
  } else {
    #ifdef DEBUG
    Serial.println(" connection failed!");
    #endif DEBUG       
    _wifiClient.stop();
    return false;
  }                           
}

void WeatherNow::_parseNowInfo(WiFiClient httpClient){
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + 230;
  DynamicJsonDocument doc(capacity);
  
  deserializeJson(doc, httpClient);
  
  JsonObject results_0 = doc["results"][0];
  
  JsonObject results_0_now = results_0["now"];
  const char* results_0_now_text = results_0_now["text"];
  const char* results_0_now_code = results_0_now["code"];
  const char* results_0_now_temperature = results_0_now["temperature"]; 
  
  const char* results_0_last_update = results_0["last_update"]; 

  // 通过串口监视器显示以上信息
  _now_text_str = results_0_now["text"].as<String>(); 
  _now_code_int = results_0_now["code"].as<int>(); 
  _now_temperature_int = results_0_now["temperature"].as<int>(); 
  
  _last_update_str = results_0["last_update"].as<String>();   

}

// 返回当前天气信息（字符串格式）
String WeatherNow::getWeatherText(){
  return _now_text_str;
}

// 返回当前天气信息（整数格式）
int WeatherNow::getWeatherCode(){
  return _now_code_int;
}

// 返回当前气温
int WeatherNow::getDegree(){
  return _now_temperature_int;
}

// 返回心知天气信息更新时间
String WeatherNow::getLastUpdate(){
  return _last_update_str;
}