#include <Arduino.h>
#include "weather.h"
#include "wifi.h"
#include "oled.h"
#include "rtc.h"
#include "mydht.h"
#include "ai.h"
int currentPage = 0;

unsigned long lastPageSwitch = 0;

unsigned long lastWeatherUpdate = 0;

void drawMainPage() {
    u8g2.setFont(u8g2_font_6x12_tr);   // 强制小字体，防止继承变大
    float t = getTemperature();
    float h = getHumidity();
    u8g2.setCursor(0, 12);
    u8g2.print(rtcGetTime());
    u8g2.setCursor(0, 26);
    u8g2.print(rtcGetDate());
    u8g2.setCursor(0, 44);
    u8g2.print("Temp:");
    u8g2.print(t);
    u8g2.print("C");
    u8g2.setCursor(0, 60);
    u8g2.print("Humi:");
    u8g2.print(h);
    u8g2.print("%");
}

void drawWeatherPage() {
    u8g2.setFont(u8g2_font_6x12_tr);   // 强制小字体
    WeatherInfo w = weatherGet();
    u8g2.setCursor(0, 12);
    u8g2.print("Weather");
    u8g2.setCursor(0, 30);
    u8g2.print("Temp:");
    u8g2.print(w.temperature);
    u8g2.print("C");
    u8g2.setCursor(0, 48);
    u8g2.print("Code:");
    u8g2.print(w.weathercode);
}

void drawWifiPage() {
    u8g2.setFont(u8g2_font_6x12_tr);   // 强制小字体
    u8g2.setCursor(0, 12);
    u8g2.print("WiFi Info");
    u8g2.setCursor(0, 30);
    if(WiFi.status() == WL_CONNECTED) {
        u8g2.print("Connected");
    } else {
        u8g2.print("Disconnected");
    }
    u8g2.setCursor(0, 48);
    u8g2.print(WiFi.localIP());
}

void drawAIPage() {
    u8g2.setFont(u8g2_font_6x12_tr);
    String result = queryAI("weather");

    u8g2.setCursor(0, 12);
    u8g2.print("AI Advice");

    // 将 result 拆分为前缀（温湿度）和建议
    // 假设 result 格式固定为 "25C 47% | Some advice here"
    int separator = result.indexOf('|');
    if (separator != -1) {
        String prefix = result.substring(0, separator + 1);  // 包含 "| "
        String advice = result.substring(separator + 1);
        u8g2.setCursor(0, 28);
        u8g2.print(prefix);
        u8g2.setCursor(0, 44);
        u8g2.print(advice);
    } else {
        // 降级：直接打印，并尝试分行
        u8g2.setCursor(0, 28);
        u8g2.print(result.substring(0, 21));
        u8g2.setCursor(0, 44);
        u8g2.print(result.substring(21));
    }
}
void drawTime() {   
    u8g2.setCursor(0, 12);
    u8g2.print(rtcGetTime());

    u8g2.setCursor(0, 24);
    u8g2.print(rtcGetDate());
}
void drawSensor() {         //
    float t = getTemperature();
    float h = getHumidity();

    u8g2.setCursor(0, 40);
    u8g2.print("T:");
    u8g2.print(t);

    u8g2.setCursor(64, 40);
    u8g2.print("H:");
    u8g2.print(h);
}
void drawWeather() {
    WeatherInfo w = weatherGet();

    u8g2.setCursor(0, 56);
    u8g2.print("W:");
    u8g2.print(w.temperature);
    u8g2.print("C");
}
void setup() {

    Serial.begin(115200);

    // 先初始化硬件
    rtcInit();

    oledInit();

    dhtInit();

    // 再联网
    wifiInit();

    wifiConnect();

    // 最后天气
    weatherInit();

    weatherUpdate();
}

void loop() {

    if (millis() - lastPageSwitch > 8000) {   // 只保留这一段
        currentPage++;
        if (currentPage > 3) currentPage = 0;
        lastPageSwitch = millis();
    }

    u8g2.clearBuffer();

    switch(currentPage) {
        case 0:
            drawMainPage();   // 时间 + 温湿度
            break;
        case 1:
            drawWeatherPage();
            break;
        case 2:
            drawWifiPage();
            break;
        case 3:
            drawAIPage();
            break;
    }

    u8g2.sendBuffer();
}