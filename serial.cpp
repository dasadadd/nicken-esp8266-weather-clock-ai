#include "serial.h"

void serialInit(uint32_t baud_rate) {
    Serial.begin(baud_rate);
}

void serialPrint(String message) {
    // 打印格式：[时间戳] 消息内容
    Serial.print("[");
    Serial.print(millis());  // 当前运行时间（毫秒）
    Serial.print("] ");
    Serial.println(message);
}
