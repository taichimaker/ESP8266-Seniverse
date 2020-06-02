/**********************************************************************
项目名称/Project          : 零基础入门学用物联网
程序名称/Program name     : weather_now
团队/Team                : 太极创客团队 / Taichi-Maker (www.taichi-maker.com)
作者/Author              : CYNO朔
日期/Date（YYYYMMDD）     : 20200602
程序目的/Purpose          : 
通过心知天气(www.seniverse.com)免费服务获取实时天气信息。
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

const char* ssid     = "taichimaker";       // 连接WiFi名（此处使用taichi-maker为示例）
                                            // 请将您需要连接的WiFi名填入引号中
const char* password = "xxxxxxxx";          // 连接WiFi密码（此处使用12345678为示例）
                                            // 请将您需要连接的WiFi密码填入引号中
 
const char* host = "api.seniverse.com";     // 将要连接的服务器地址  
const int httpPort = 80;                    // 将要连接的服务器端口      

// 心知天气HTTP请求所需信息
String reqUserKey = "SCXC4Mj_0aB96cZup";   // 私钥
String reqLocation = "beijing";            // 城市
String reqUnit = "c";                      // 摄氏/华氏

void setup(){
  Serial.begin(9600);          
  Serial.println("");
  
  // 设置开发板LED引脚
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  connectWiFi();
}
 
void loop(){
  String reqRes = "/v3/weather/now.json?key=" + reqUserKey +
                  + "&location=" + reqLocation + 
                  "&language=en&unit=" +reqUnit;
                  
  httpRequest(reqRes);
  delay(3000);
}
 
// 向服务器请求信息并对信息进行解析
void httpRequest(String reqRes){
  WiFiClient client;
 
  String httpRequest = String("GET ") + reqRes + " HTTP/1.1\r\n" + 
                              "Host: " + host + "\r\n" + 
                              "Connection: close\r\n\r\n";
  Serial.println(""); 
  Serial.print("Connecting to "); Serial.print(host);
  
  if (client.connect(host, 80)){
    Serial.println(" Success!");
 
    // 向服务器发送http请求信息
    client.print(httpRequest);
    Serial.println("Sending request: ");
    Serial.println(httpRequest);  
 
    // 获取并显示服务器响应状态行 
    String status_response = client.readStringUntil('\n');
    Serial.print("status_response: ");
    Serial.println(status_response);
 
    // 使用find跳过HTTP响应头
    if (client.find("\r\n\r\n")) {
      Serial.println("Found Header End. Start Parsing.");
    }

    //String serverPayLoad = client.readString();
    //Serial.print(serverPayLoad);
    parseInfo(client); 
  }
  else {
    Serial.println(" connection failed!");
  }   
  //断开客户端与服务器连接工作
  client.stop(); 
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

// 利用ArduinoJson库解析心知天气响应信息
void parseInfo(WiFiClient client){
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(6) + 230;
  DynamicJsonDocument doc(capacity);
  
  deserializeJson(doc, client);
  
  JsonObject results_0 = doc["results"][0];
  
  JsonObject results_0_now = results_0["now"];
  const char* results_0_now_text = results_0_now["text"]; // "Sunny"
  const char* results_0_now_code = results_0_now["code"]; // "0"
  const char* results_0_now_temperature = results_0_now["temperature"]; // "32"
  
  const char* results_0_last_update = results_0["last_update"]; // "2020-06-02T14:40:00+08:00" 

  // 通过串口监视器显示以上信息
  String results_0_now_text_str = results_0_now["text"].as<String>(); 
  int results_0_now_code_int = results_0_now["code"].as<int>(); 
  int results_0_now_temperature_int = results_0_now["temperature"].as<int>(); 
  
  String results_0_last_update_str = results_0["last_update"].as<String>();   

  Serial.println(F("======Weahter Now======="));
  Serial.print(F("Weather Now: "));
  Serial.print(results_0_now_text_str);
  Serial.print(F(" "));
  Serial.println(results_0_now_code_int);
  Serial.print(F("Temperature: "));
  Serial.println(results_0_now_temperature_int);
  Serial.print(F("Last Update: "));
  Serial.println(results_0_last_update_str);
  Serial.println(F("========================"));
}

/*
当前天气
api.seniverse.com/v3/weather/now.json?key=xxxxxxxxxxxx&location=beijing&language=en&unit=c

3日英文天气预报：
api.seniverse.com/v3/weather/daily.json?key=xxxxxxxxxxxx&location=beijing&language=en&unit=c&start=0&days=3

生活指数
api.seniverse.com/v3/life/suggestion.json?key=xxxxxxxxxxxx&location=beijing&language=en
*/
