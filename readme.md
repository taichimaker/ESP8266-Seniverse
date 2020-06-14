# ESP8266 心知天气库  / ESP8266-Seniverse

*English description can be found at the end of Chinese description.*

## 基本介绍


此库用于ESP8266物联网开发板通过HTTP协议获取心知天气网站API所提供的免费信息。这些信息包括：

1. 天气预报信息（温度，天气，降水概率，风力，风向，湿度）
2. 实时天气信息（温度，天气）
3. 获取实时生活指数（穿衣，紫外线强度，洗车，旅游，感冒，运动）

关于以上信息的详细说明，请参考心知天气网站官方文档：https://www.seniverse.com/docs

心知天气成立于2016年，是中国领先的气象数据服务公司，致力于提供高精度的气象数据服务和产品。心知天气官网地址：www.seniverse.com 

## 关于本库

本库为太极创客团队制作的免费视频教程《零基础入门学用物联网 》中一部分。该教程系统的向您讲述ESP8266的物联网应用相关的软件和硬件知识。如果您希望观看教程视频，可前往以下视频平台观看。

哔哩哔哩：https://www.bilibili.com/video/BV1L7411c7jw

YouTube: https://www.youtube.com/playlist?list=PL8mx3Pk-gVLI2GwuxuqR_T5WDKeAPRkzj

ESP8266-Seniverse库仅仅是我们团队所开发的诸多免费开源项目中的一个。我们坚持免费开源是为了让更多的朋友可以体会开源项目和开源协作的魅力，让我们开发的项目更富活力。假如您喜欢我们的项目，请为本项目打上一颗小星星，或者把我们推荐给更多热爱科技的朋友们。谢谢！您的鼓励是我们前进最大的动力！

## 使用前准备工作

1. 使用本库前请预先注册好心知天气账号并且开通免费服务。
2. 本程序使用Arduino编程语言。如您使用Arduino IDE开发，请预先在Arduino IDE中安装好ESP8266扩展程序，如需了解详细安装方法，请参考太极创客团队制作的[《零基础入门学用物联网 - 基础知识篇》3-1-2 为ESP8266-NodeMCU搭建Arduino IDE开发环境](http://www.taichi-maker.com/homepage/esp8266-nodemcu-iot/iot-c/nodemcu-arduino-ide/)。
3. 本程序使用ArduinoJson库
   请预先在Arduino IDE中安装[ArduinoJson库](www.arduinojson.org)。 如果您想了解该库的具体使用方法，请参考太极创客团队制作的免费视频教程《[零基础入门学用物联网](http://www.taichi-maker.com/homepage/esp8266-nodemcu-iot/)》

## 使用方法

### 获取当前天气信息

1. 您可以参考 **example** 目录中的 **weather_now** 程序了解具体使用方法

2. 首先通过`WeatherNow`建立对象
   ```C++
   WeatherNow weatherNow
   ```
   
3. 使用`config`函数配置连接心知天气的用户私钥、城市信息以及温度
   ```C++
   weatherNow.config(reqUserKey, reqLocation, reqUnit);
   ```

4. 使用`update`函数对天气信息进行更新（此函数返回值为`bool`型。在ESP8266成功连接心知天气服务器并且服务器返回响应状态码为`200`时，此函数将会返回真，否则会返回假。）
   ```C++
   weatherNow.update();
   ```

5. 使用下列函数获取当前天气信息  

   | 函数说明                          | 函数示例                      |
   | --------------------------------- | ----------------------------- |
   | 当前天气信息 (返回值类型：String) | `weatherNow.getWeatherText()` |
   | 当前天气代码 (返回值类型：int)    | `weatherNow.getWeatherCode()` |
   | 当前温度信息 (返回值类型：int)    | `weatherNow.getDegree()`      |

6. 使用`getServerCode`函数可获取服务器响应状态码。  
   当用户通过ESP8266向心知天气服务器发送的请求存在问题时（如私钥错误、请求信息内容错误等），服务器会通过响应状态码告知用户问题的具体原因。您可以通过心知天气的官方文档获得服务器响应状态码所对应的具体问题原因。
   ```C++
   weatherNow.getServerCode()
   ```

7. 使用`getLastUpdate`函数获取心知天气信息更新时间
   ```C++
   weatherNow.getLastUpdate()
   ```

### 获取天气预报信息

1. 您可以参考**example**目录中的**forecast**程序了解具体使用方法

2. 首先通过`Forecast`建立对象
   ```C++
   Forecast forecast
   ```

3. 使用`config`函数配置连接心知天气的用户私钥、城市信息以及温度
   ```C++
   forecast.config(reqUserKey, reqLocation, reqUnit);
   ```

4. 使用`update`函数对天气信息进行更新（此函数返回值为`bool`型。在ESP8266成功连接心知天气服务器并且服务器返回响应状态码为`200`时，此函数将会返回真，否则会返回假。）
   ```C++
   forecast.update();
   ```

5. 使用下列函数获取当前天气信息 （下列函数的参数i为获取第几天信息的天数序号。例：参数为`0`，则函数将会返回今天的天气预报信息。参数为`1`，则返回明天的天气预报...依此类推。参数i取值范围为`0-2`。）

   | 函数说明                                 | 函数示例（参数i为第几天信息）  |
   | ---------------------------------------- | ------------------------------ |
   | 白天天气信息(返回值类型：String)         | `forecast.getDayText(i)`       |
   | 白天天气代码(返回值类型：int)            | `forecast.getDayCode(i)`       |
   | 夜晚天气信息(返回值类型：String)         | `forecast.getNightText(i)`     |
   | 夜晚天气代码(返回值类型：int)            | `forecast.getNightCode(i)`     |
   | 最高气温(返回值类型：int)                | `forecast.getHigh(i)`          |
   | 最低气温(返回值类型：int)                | `forecast.getLow(i)`           |
   | 心知天气信息更新时间(返回值类型：String) | `forecast.getLastUpdate(i)`    |
   | 获取降水概率信息(返回值类型：float)      | `forecast.getRain(i)`          |
   | 获取风向信息(返回值类型：String)         | `forecast.getWindDirection(i)` |
   | 获取风速信息(返回值类型：float)          | `forecast.getWindSpeed(i)`     |
   | 获取风力信息(返回值类型：int)            | `forecast.getWindScale(i)`     |
   | 获取湿度信息(返回值类型：int)            | `forecast.getHumidity(i)`      |

6. 使用`getServerCode`函数可获取服务器响应状态码。  
   当用户通过ESP8266向心知天气服务器发送的请求存在问题时（如私钥错误、请求信息内容错误等），服务器会通过响应状态码告知用户问题的具体原因。您可以通过心知天气的官方文档获得服务器响应状态码所对应的具体问题原因。
   ```C++
   forecast.getServerCode()
   ```

7. 使用`getLastUpdate`函数获取心知天气信息更新时间
   ```C++
   forecast.getLastUpdate()
   ```

### 获取生活指数信息

1. 您可以参考 **example** 目录中的 **life_info** 程序了解具体使用方法

2. 首先通过`LIfeInfo`建立对象
   ```C++
   LifeInfo lifeInfo
   ```

3. 使用`config`函数配置连接心知天气的用户私钥、城市信息以及温度
   ```C++
   lifeInfo.config(reqUserKey, reqLocation, reqUnit);
   ```

4. 使用`update`函数对天气信息进行更新（此函数返回值为`bool`型。在ESP8266成功连接心知天气服务器并且服务器返回响应状态码为`200`时，此函数将会返回真，否则会返回假。）
   ```C++
   lifeInfo.update();
   ```

5. 使用下列函数获取当前天气信息  

   | 函数说明                           | 函数示例                  |
   | ---------------------------------- | ------------------------- |
   | 获取洗车建议(返回值类型：String)   | `lifeInfo.getCarWash()`   |
   | 获取穿衣建议(返回值类型：String)   | `lifeInfo.getDressing()`  |
   | 获取流感建议(返回值类型：String)   | `lifeInfo.getFactorFlu()` |
   | 获取运动建议(返回值类型：String)   | `lifeInfo.getExercise()`  |
   | 获取旅游建议(返回值类型：String)   | `lifeInfo.getTravel()`    |
   | 获取紫外线建议(返回值类型：String) | `lifeInfo.getUV()`        |

6. 使用`getServerCode`函数可获取服务器响应状态码。  
当用户通过ESP8266向心知天气服务器发送的请求存在问题时（如私钥错误、请求信息内容错误等），服务器会通过响应状态码告知用户问题的具体原因。您可以通过心知天气的官方文档获得服务器响应状态码所对应的具体问题原因。
   ```C++
   lifeInfo.getServerCode()
   ```
7. 使用`getLastUpdate`函数获取心知天气信息更新时间
   ```C++  
   lifeInfo.getLastUpdate()
   ```

太极创客团队信息
--------
太极创客官网地址：http://www.taichi-maker.com/

太极创客哔哩哔哩主页：https://space.bilibili.com/103589285

太极创客YouTube：https://www.youtube.com/channel/UC8EkxMr5gGnrb9adVgR-UJw

太极创客GitHub：https://github.com/taichi-maker

太极创客码云：https://gitee.com/taijichuangke

-----------------------------

## ESP8266-Seniverse

This ESP8266-Arduino Library is for getting weather information from Seniverse API (Free) via HTTP protocol. The information includes:

1. Weather Forecast（Temperature，Weather，Precipitation probability，Wind Scale，Wind Direction，Humidity）
2. Live Weather Info.（Temperature，Weather）
3. Daily Life Information（Dressing Suggestion，UV level etc.）

For more infromation about the above information please refer to Seniverse API Doc (Chinese Only)：https://www.seniverse.com/docs

founded in 2016, Seniverse is a leading Weather Data provider in China. Seniverse Official Website：www.seniverse.com 

About Taichi-Maker Team
--------

Taichi-Maker Official Website：http://www.taichi-maker.com/

Taichi-Maker BiliBili：https://space.bilibili.com/103589285

Taichi-Maker YouTube Chanel：https://www.youtube.com/channel/UC8EkxMr5gGnrb9adVgR-UJw

Taichi-Maker GitHub：https://github.com/taichi-maker

Taichi-Maker Gitee：https://gitee.com/taijichuangke



