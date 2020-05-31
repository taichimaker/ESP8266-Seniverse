# ESP8266 心知天气

此库中示例程序用于使用ESP8266获取心知天气（www.seniverse.com）信息。

本项目为太极创客团队制作的免费视频教程《零基础入门学用物联网 》中一部分。该教程系统的向您讲述ESP8266的物联网应用相关的软件和硬件知识。如果您希望观看教程视频，可前往以下视频平台观看。

哔哩哔哩：https://www.bilibili.com/video/BV1L7411c7jw

YouTube: https://www.youtube.com/playlist?list=PL8mx3Pk-gVLI2GwuxuqR_T5WDKeAPRkzj

假如您想了解更多太极创客的教程项目和相关内容，欢迎您前往我们的网站：

www.taichi-maker.com

## 基本功能

通过心知天气免费服务获取以下信息：

1. 获取天气预报信息（三日）
2. 获取实时天气信息
3. 获取实时生活指数（穿衣，紫外线强度，洗车，旅游，感冒，运动）

## 使用前准备工作

1. 使用本库前请预先注册好心知天气账号并且开通免费服务。
2. 本程序使用Arduino编程语言。如您使用Arduino IDE开发，请预先在Arduino IDE中安装好ESP8266扩展程序，如需了解详细安装方法，请参考太极创客团队制作的[《零基础入门学用物联网 - 基础知识篇》3-1-2 为ESP8266-NodeMCU搭建Arduino IDE开发环境](http://www.taichi-maker.com/homepage/esp8266-nodemcu-iot/iot-c/nodemcu-arduino-ide/)。
3. 本程序使用ArduinoJson库
   请预先在Arduino IDE中安装[ArduinoJson库](www.arduinojson.org)。 如果您想了解该库的具体使用方法，请参考太极创客团队制作的[《零基础入门学用物联网 - 基础知识篇》