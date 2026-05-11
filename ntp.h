#ifndef NTP_H
#define NTP_H

#include <Arduino.h>
#include <NTPClient.h>
#include <WiFiUdp.h>   //NTP初始化时候，需要依赖一个UDP的对象，所以需要包含进来

// 初始化NTP客户端，设置NTP服务器和时区
void ntpInit();

// 获取当前时间
// @return: 格式化的时间字符串 (HH:MM:SS)
String ntpGetTime();

// 获取当前日期
// @return: 格式化的日期字符串 (YYYY-MM-DD)
String ntpGetDate();

// 同步网络时间
// @return: 同步是否成功
bool ntpSync();

#endif // NTP_H
