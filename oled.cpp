#include "oled.h"
#include "serial.h"
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
void oledInit() {
    u8g2.begin();
    u8g2.setFont(u8g2_font_6x12_tr);   // 恢复原来小字体，所有页面恢复正常大小
    u8g2.clearBuffer();
    u8g2.sendBuffer();
}
void oledShow(uint8_t x, uint8_t y, String text) {
    
    u8g2.setCursor(x, y);
    u8g2.print(text);
    u8g2.sendBuffer();
}
void oledClear() {
    // 清空显示缓冲区并刷新显示
    u8g2.clearBuffer();
    u8g2.sendBuffer();
}