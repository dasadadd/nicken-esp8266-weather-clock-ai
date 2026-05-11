#ifndef OLED_H
#define OLED_H

#include <Arduino.h>
#include <U8g2lib.h>
// 在 oled.h 最上方，extern 之前加入
#include <U8g2lib.h>  // 确保已包含
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
// 声明外部u8g2对象，用于OLED显示
// 初始化OLED显示屏，设置字体和UTF8支持
void oledInit();
// 在指定位置显示文本
// @param x: 横坐标（像素）
// @param y: 纵坐标（像素）
// @param text: 要显示的文本
void oledShow(uint8_t x, uint8_t y, String text);
// 清除OLED显示内容
void oledClear();
#endif // OLED_H
