#ifndef RTC_H
#define RTC_H

//C/C++中的头文件保护机制（也称为宏保护或include保护），用于防止头文件被重复包含，确保编译过程的正确性和效率。

#include <Arduino.h>

void rtcInit();
String rtcGetTime();
String rtcGetDate();

#endif