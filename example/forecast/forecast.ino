/**********************************************************************
项目名称/Project          : 零基础入门学用物联网
程序名称/Program name     : forecast（rev.001）
团队/Team                : 太极创客团队 / Taichi-Maker (www.taichi-maker.com)
作者/Author              : CYNO朔
日期/Date（YYYYMMDD）     : 初版建立时间20200603
程序目的/Purpose          : 
使用ESP8266_Seniverse库通过心知天气服务器获取天气预报信息
-----------------------------------------------------------------------
本程序所属仓库网址
GitHub: https://github.com/taichi-maker/ESP8266-Seniverse
Gitee: https://gitee.com/taijichuangke/ESP8266-Seniverse
-----------------------------------------------------------------------
其它说明 / Other Description
心知天气API文档说明: https://www.seniverse.com/docs

本程序为太极创客团队制作的免费视频教程《零基础入门学用物联网 》中一部分。该教程系统的
向您讲述ESP8266的物联网应用相关的软件和硬件知识。以下是该教程目录页：
http://www.taichi-maker.com/homepage/esp8266-nodemcu-iot/                                
***********************************************************************/
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266_Seniverse.h>

const char* ssid     = "taichimaker";       // 连接WiFi名（此处使用taichi-maker为示例）
                                            // 请将您需要连接的WiFi名填入引号中
const char* password = "12345678";          // 连接WiFi密码（此处使用12345678为示例）
                                            // 请将您需要连接的WiFi密码填入引号中

// 心知天气API请求所需信息
// 请对以下信息进行修改，填入您的心知天气私钥以及需要获取天气信息的城市和温度单位
// 如需进一步了解心知天气API所提供的城市列表等信息，请前往心知天气官方产品文档网址：
// https://www.seniverse.com/docs
String reqUserKey = "XXXXXXXXXXXXXXXXX";   // 私钥
String reqLocation = "beijing";            // 城市
String reqUnit = "c";                      // 摄氏/华氏// 请将您需要连接的WiFi密码填入引号中

Forecast forecast; // 建立Forecast对象用于获取心知天气信息

void setup(){
  Serial.begin(9600);          
  Serial.println("");

  connectWiFi();    // 连接wifi

  // 配置心知天气请求信息
  forecast.config(reqUserKey, reqLocation, reqUnit);
}
 
void loop(){
  if(forecast.update()){  // 更新天气信息
    for(int i = 0; i < 3; i++){
      Serial.print(F("========Day ")); 
      Serial.print(i);      
      Serial.println(F("========"));     
      
      Serial.print(F("Day Weather: "));
      Serial.print(forecast.getDayText(i));  
      Serial.print(F(" "));
      Serial.println(forecast.getDayCode(i));  
      Serial.print(F("Night Weather: "));
      Serial.print(forecast.getNightText(i));  
      Serial.print(F(" "));
      Serial.println(forecast.getNightCode(i));  
      Serial.print(F("High: "));
      Serial.print(forecast.getHigh(i));
      Serial.println(F("°C"));     
      Serial.print(F("LOW: "));
      Serial.print(forecast.getLow(i));  
      Serial.println(F("°C"));

      Serial.print(F("Rainfall: "));
      Serial.print(forecast.getRain(i));  
      Serial.println(F("%"));
      Serial.print(F("Wind Direction: "));
      Serial.println(forecast.getWindDirection(i));  
      Serial.print(F("Wind Speed: "));
      Serial.println(forecast.getWindSpeed(i));
      Serial.print(F("Wind Scale: "));
      Serial.println(forecast.getWindScale(i));    
      Serial.print(F("Humidity: "));
      Serial.println(forecast.getHumidity(i)); 
                    
      Serial.print(F("Last Update: "));       
      Serial.println(forecast.getLastUpdate());                
    }
    Serial.print(F("Server Code: ")); 
    Serial.println(forecast.getServerCode()); 
    Serial.println(F("====================="));   
  } else {    // 更新失败
    Serial.println("Update Fail...");   
    //Serial.print("Server Response: ");          // 输出服务器响应状态码供用户查找问题
    //Serial.println(weatherNow.getServerCode()); // 心知天气服务器错误代码说明可通过以下网址获取
  }                                             // https://docs.seniverse.com/api/start/error.html
  
  delay(3000);
}

// 连接WiFi
void connectWiFi(){
  WiFi.begin(ssid, password);                  // 启动网络连接
  Serial.print("Connecting to ");              // 串口监视器输出网络连接信息
  Serial.print(ssid); Serial.println(" ...");  // 告知用户NodeMCU正在尝试WiFi连接
  
  int i = 0;                                   // 这一段程序语句用于检查WiFi是否连接成功
  while (WiFi.status() != WL_CONNECTED) {      // WiFi.status()函数的返回值是由NodeMCU的WiFi连接状态所决定的。 
    delay(1000);                               // 如果WiFi连接成功则返回值为WL_CONNECTED                       
    Serial.print(i++); Serial.print(' ');      // 此处通过While循环让NodeMCU每隔一秒钟检查一次WiFi.status()函数返回值
  }                                            // 同时NodeMCU将通过串口监视器输出连接时长读秒。
                                               // 这个读秒是通过变量i每隔一秒自加1来实现的。                                              
  Serial.println("");                          // WiFi连接成功后
  Serial.println("Connection established!");   // NodeMCU将通过串口监视器输出"连接成功"信息。
  Serial.print("IP address:    ");             // 同时还将输出NodeMCU的IP地址。这一功能是通过调用
  Serial.println(WiFi.localIP());              // WiFi.localIP()函数来实现的。该函数的返回值即NodeMCU的IP地址。  
}
