#include "rtc.h"//自己写的接口声明
#include <Wire.h>//I2C通信库（让单片机能和外设说话）  控制 SDA / SCL 这两根线的“司机”
#include "RTClib.h" //DS3231的“高级封装库” 如果没有它，你要自己写：I2C读写  寄存器地址   时间解析
                                           //有了它：rtc.now()  一行搞定

RTC_DS3231 rtc;    //创建一个“DS3231设备对象”

void rtcInit() {
      Wire.begin(D2, D1);    //告诉ESP8266：SDA → D2  SCL → D1
   // rtc.begin();   //初始化 DS3231 芯片 检查芯片是否存在  初始化通信
   delay(100);
     if (!rtc.begin()) {

    Serial.println("RTC初始化失败");

    return;
}

    if (rtc.lostPower()) {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    }
}

String rtcGetTime() {
    DateTime now = rtc.now();   
//rtc.now()   从 DS3231 读取当前时间  
//DateTime now 返回一个对象：

    char buf[9];
    sprintf(buf, "%02d:%02d:%02d",               //sprintf(...)把数据“拼成字符串”
            now.hour(), now.minute(), now.second());

    return String(buf);
}

String rtcGetDate() {//获取日期函数
    DateTime now = rtc.now();

    char buf[11];
    sprintf(buf, "%04d-%02d-%02d",
            now.year(), now.month(), now.day());

    return String(buf);
}

//这个 rtc.cpp 本质做了三件事：
//✅ 1. 初始化通信
//Wire → I2C通信
//rtc.begin → 芯片启动
//✅ 2. 获取时间数据
//rtc.now() → 读取芯片内部时间
//✅ 3. 转成字符串
//DateTime → String
//👉 为了给 OLED 用