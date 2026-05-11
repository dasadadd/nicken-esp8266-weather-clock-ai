#ifndef SERIAL_H
#define SERIAL_H

#include <Arduino.h>

// 初始化串口通信，设置波特率
// @param baud_rate: 串口波特率，默认115200
void serialInit(uint32_t baud_rate = 115200);

// 打印调试信息到串口，自动添加时间戳
// @param message: 要打印的信息
void serialPrint(String message);

#endif // SERIAL_H