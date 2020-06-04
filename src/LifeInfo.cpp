#include "LifeInfo.h"
 
LifeInfo::LifeInfo(){
}

/* 配置心知天气请求信息
 * @param userKey  用户心知天气私钥
 * @param location 获取信息的城市参数
 * @param location 获取信息的温度单位(摄氏/华氏)
 */
void LifeInfo::config(String userKey, String location, String unit){
  _reqUserKey = userKey; 
  _reqLocation = location;
}

/* 尝试从心知天气更新信息
 * @return bool 成功更新返回真，否则返回假
 */
bool LifeInfo::update(){
  WiFiClient _wifiClient;
                  
  String reqRes = "/v3/life/suggestion.json?key=" + _reqUserKey +
                  + "&location=" + _reqLocation + 
                  "&language=en";
                                    
  String httpRequest = String("GET ") + reqRes + " HTTP/1.1\r\n" + 
                              "Host: " + _host + "\r\n" + 
                              "Connection: close\r\n\r\n";
                              
  #ifdef DEBUG
  Serial.print("Connecting to ");Serial.print(_host);
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
    String _status_response = _wifiClient.readStringUntil('\n');
    #ifdef DEBUG
    Serial.print("_status_response: ");
    Serial.println(_status_response);
    #endif DEBUG
    
    // 查验服务器是否响应200 OK
    _response_code = _status_response.substring(9, 12);
    if (_response_code == "200") {
      #ifdef DEBUG
      Serial.println("Response Code: 200");
      #endif DEBUG 
    } else {
      #ifdef DEBUG
      Serial.println(F("Response Code: NOT 200"));
      #endif DEBUG   
      _wifiClient.stop();    
      return false;
    }  

    // 使用find跳过HTTP响应头
    if (_wifiClient.find("\r\n\r\n")) {
      #ifdef DEBUG
      Serial.println("Found Header End. Start Parsing.");
      #endif DEBUG              
    }
    
    _parseLifeInfo(_wifiClient); 
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

// 利用ArduinoJson库解析心知天气响应信息
void LifeInfo::_parseLifeInfo(WiFiClient client){
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 6*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(3) + 2*JSON_OBJECT_SIZE(6) + 400;
  DynamicJsonDocument doc(capacity);
  
  deserializeJson(doc, client);
  
  JsonObject results_0 = doc["results"][0];  
  JsonObject results_0_suggestion = results_0["suggestion"];

  _carWash = results_0_suggestion["car_washing"]["brief"].as<String>(); 
  _dressing = results_0_suggestion["dressing"]["brief"].as<String>();  
  _factorFlu = results_0_suggestion["flu"]["brief"].as<String>();   
  _exercise = results_0_suggestion["sport"]["brief"].as<String>();   
  _travel = results_0_suggestion["travel"]["brief"].as<String>();   
  _uv = results_0_suggestion["uv"]["brief"].as<String>();   
  _last_update_str = results_0["last_update"].as<String>(); 
}

// 获取洗车建议
String LifeInfo::getCarWash(){
  return _carWash;
}

// 获取穿衣建议 
String LifeInfo::getDressing(){
  return _dressing;
}

// 获取流感建议     
String LifeInfo::getFactorFlu(){
  return _factorFlu;
}

// 获取运动建议          
String LifeInfo::getExercise(){
  return _exercise;
}

// 获取旅游建议        
String LifeInfo::getTravel(){
  return _travel;
}

// 获取紫外线建议            
String LifeInfo::getUV(){
  return _uv;
}

// 返回心知天气信息更新时间
String LifeInfo::getLastUpdate(){
  return _last_update_str;
}

// 返回服务器响应状态码
String LifeInfo::getServerCode(){
  return _response_code;
}
