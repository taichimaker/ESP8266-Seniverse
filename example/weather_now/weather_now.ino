/**********************************************************************
项目名称/Project          : 零基础入门学用物联网
程序名称/Program name     : weather_now（rev.002）
团队/Team                : 太极创客团队 / Taichi-Maker (www.taichi-maker.com)
作者/Author              : CYNO朔
日期/Date（YYYYMMDD）     : 初版建立时间20200602(最新修订时间20200607)
程序目的/Purpose          : 
使用ESP8266_Seniverse库通过心知天气服务器获取实时天气信息。
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
const char* password = "12345678";          // 连接WiFi密码（此处使用12345678为示例）                                         // 请将您需要连接的WiFi密码填入引号中
                                            // 请将您需要连接的WiFi密码填入引号中

// 心知天气HTTP请求所需信息
// 请对以下信息进行修改，填入您的心知天气私钥以及需要获取天气信息的城市和温度单位
// 如需进一步了解心知天气API所提供的城市列表等信息，请前往心知天气官方产品文档网址：
// https://www.seniverse.com/docs
String reqUserKey = "XXXXXXXXXXXXXXXXX";   // 私钥
String reqLocation = "beijing";            // 城市
String reqUnit = "c";                      // 摄氏/华氏

WeatherNow weatherNow;  // 建立WeatherNow对象用于获取心知天气信息

void setup(){
  Serial.begin(9600);          
  Serial.println("");

  connectWiFi();    // 连接wifi

  // 配置心知天气请求信息
  weatherNow.config(reqUserKey, reqLocation, reqUnit);
}
 
void loop(){
  if(weatherNow.update()){  // 更新天气信息
    Serial.println(F("======Weahter Info======"));
    Serial.print("Server Response: ");
    Serial.println(weatherNow.getServerCode()); // 获取服务器响应码
    Serial.print(F("Weather Now: "));
    Serial.print(weatherNow.getWeatherText());  // 获取当前天气（字符串格式）
    Serial.print(F(" "));
    Serial.println(weatherNow.getWeatherCode());// 获取当前天气（整数格式）
    Serial.print(F("Temperature: "));
    Serial.println(weatherNow.getDegree());     // 获取当前温度数值
    Serial.print(F("Last Update: "));
    Serial.println(weatherNow.getLastUpdate()); // 获取服务器更新天气信息时间
    Serial.println(F("========================"));     
  } else {    // 更新失败
    Serial.println("Update Fail...");   
    Serial.print("Server Response: ");          // 输出服务器响应状态码供用户查找问题
    Serial.println(weatherNow.getServerCode()); // 心知天气服务器错误代码说明可通过以下网址获取
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
/*-----------------------------------------------------------------------
修订历史/Revision History  
日期/Date    作者/Author      参考号/Ref    修订说明/Revision Description
20200603      CYNO朔           001        add http response code check
20200603      CYNO朔           002        change file name to ESP8266_Seniverse
-----------------------------------------------------------------------*/                                 
