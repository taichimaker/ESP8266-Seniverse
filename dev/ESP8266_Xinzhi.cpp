#include "ESP8266_Xinzhi.h"
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
 
WeatherNow::WeatherNow(){
}
 
void WeatherNow::config(String userKey, String location, String unit){
  _reqUserKey = userKey; 
  location = _reqLocation;
  unit = _reqUnit;
}
