#include "Forecast.h"

Forecast::Forecast(){
}

/* 配置心知天气请求信息
 * @param userKey  用户心知天气私钥
 * @param location 获取信息的城市参数
 * @param location 获取信息的温度单位(摄氏/华氏)
 */
void Forecast::config(String userKey, String location, String unit){
  _reqUserKey = userKey; 
  _reqLocation = location;
  _reqUnit = unit;
}

/* 尝试从心知天气更新天气预报信息
 * @return: bool 成功更新返回真，否则返回假
 */
bool Forecast::update(){
  WiFiClient _wifiClient;
  
  String reqRes = "/v3/weather/daily.json?key=" +  _reqUserKey +
                  + "&location=" + _reqLocation + "&language=en&unit=" +
                  _reqUnit + "&start=0&days=3";                  
                  
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
    
    // 解析服务器响应信息
    _parseForecastInfo(_wifiClient); 
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

// 解析服务器响应信息
void Forecast::_parseForecastInfo(WiFiClient httpClient){
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_ARRAY_SIZE(3) + JSON_OBJECT_SIZE(1) + JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + 3*JSON_OBJECT_SIZE(14) + 860;
  
  DynamicJsonDocument doc(capacity);
  
  deserializeJson(doc, httpClient);
  
  JsonObject results_0 = doc["results"][0];
  
  JsonArray results_0_daily = results_0["daily"];
  
  JsonObject results_0_daily_0 = results_0_daily[0]; 
  JsonObject results_0_daily_1 = results_0_daily[1]; 
  JsonObject results_0_daily_2 = results_0_daily[2];
  
  // 从以上信息中解析数值
  _text_day[0] = results_0_daily_0["text_day"].as<String>(); 
  _code_day[0] = results_0_daily_0["code_day"].as<int>(); 
  _text_night[0] = results_0_daily_0["text_night"].as<String>(); 
  _code_night[0] = results_0_daily_0["code_night"].as<int>(); 
  _degree_high[0] = results_0_daily_0["high"].as<int>();
  _degree_low[0] = results_0_daily_0["low"].as<int>();
  
  _rainfall[0] = results_0_daily_0["rainfall"].as<float>();
  _wind_direction[0] = results_0_daily_0["wind_direction"].as<String>();
  _wind_speed[0] = results_0_daily_0["wind_speed"].as<float>();
  _wind_scale[0] = results_0_daily_0["wind_scale"].as<int>();
  _humidity[0] = results_0_daily_0["humidity"].as<int>();   
  
  _text_day[1] = results_0_daily_1["text_day"].as<String>(); 
  _code_day[1] = results_0_daily_1["code_day"].as<int>(); 
  _text_night[1] = results_0_daily_1["text_night"].as<String>(); 
  _code_night[1] = results_0_daily_1["code_night"].as<int>(); 
  _degree_high[1] = results_0_daily_1["high"].as<int>();
  _degree_low[1] = results_0_daily_1["low"].as<int>();

  _rainfall[1] = results_0_daily_1["rainfall"].as<float>();
  _wind_direction[1] = results_0_daily_1["wind_direction"].as<String>();
  _wind_speed[1] = results_0_daily_1["wind_speed"].as<float>();
  _wind_scale[1] = results_0_daily_1["wind_scale"].as<int>();
  _humidity[1] = results_0_daily_1["humidity"].as<int>();   

  _text_day[2] = results_0_daily_2["text_day"].as<String>(); 
  _code_day[2] = results_0_daily_2["code_day"].as<int>(); 
  _text_night[2] = results_0_daily_2["text_night"].as<String>(); 
  _code_night[2] = results_0_daily_2["code_night"].as<int>(); 
  _degree_high[2] = results_0_daily_2["high"].as<int>();
  _degree_low[2] = results_0_daily_2["low"].as<int>();

  _rainfall[2] = results_0_daily_2["rainfall"].as<float>();
  _wind_direction[2] = results_0_daily_2["wind_direction"].as<String>();
  _wind_speed[2] = results_0_daily_2["wind_speed"].as<float>();
  _wind_scale[2] = results_0_daily_2["wind_scale"].as<int>();
  _humidity[2] = results_0_daily_2["humidity"].as<int>();   
  
  _last_update = results_0["last_update"].as<String>();
}

// 返回白天天气（字符串格式）
String Forecast::getDayText(int index){
  return _text_day[index];
}

// 返回白天天气（整数格式）
int Forecast::getDayCode(int index){
  return _code_day[index];
}

// 返回夜晚天气（字符串格式）
String Forecast::getNightText(int index){
  return _text_night[index];
}

// 返回夜晚天气（整数格式）
int Forecast::getNightCode(int index){
  return _code_night[index];
}

// 返回最高气温
int Forecast::getHigh(int index){
  return _degree_high[index];
}

// 返回最低气温
int Forecast::getLow(int index){
  return _degree_low[index];
}

// 返回降水概率
float Forecast::getRain(int index){
  return _rainfall[index];
}

// 获取风向信息
String Forecast::getWindDirection(int index){
  return _wind_direction[index];
}

// 获取风速信息
float Forecast::getWindSpeed(int index){
  return _wind_speed[index];
}

// 获取风力信息
int Forecast::getWindScale(int index){
  return _wind_scale[index];
}

//  获取湿度信息
int Forecast::getHumidity(int index){
  return _humidity[index];
}

// 返回心知天气信息更新时间
String Forecast::getLastUpdate(){
  return _last_update;
}


// 返回服务器响应状态码
String Forecast::getServerCode(){
  return _response_code;
}
