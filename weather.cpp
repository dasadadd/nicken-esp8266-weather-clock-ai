#include "weather.h"

#include <ESP8266WiFi.h>   // 新增这一行，解决WiFi未声明错误
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#define WEATHER_URL "http://api.open-meteo.com/v1/forecast?latitude=35.2333&longitude=115.4333&current_weather=true"

static WeatherInfo weatherInfoData;

void weatherInit() {

    weatherInfoData.temperature = "--";

    weatherInfoData.weathercode = -1;
}

bool weatherUpdate() {
    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("WiFi未连接，跳过天气更新");
        return false;
    }

    WiFiClient client;
    HTTPClient http;
    Serial.println("开始请求天气");

    http.setTimeout(10000);  // 增加到10秒，适应网络波动
    http.setFollowRedirects(HTTPC_STRICT_FOLLOW_REDIRECTS);

    if (!http.begin(client, WEATHER_URL)) {
        Serial.println("http.begin失败");
        return false;
    }

    int httpCode = http.GET();
    Serial.print("HTTP Code: ");
    Serial.println(httpCode);

    if (httpCode == HTTP_CODE_OK) {
        String payload = http.getString();
        Serial.println(payload);

        DynamicJsonDocument doc(1024);
        DeserializationError error = deserializeJson(doc, payload);
        if (error) {
            Serial.print("JSON失败: ");
            Serial.println(error.c_str());
            http.end();
            return false;
        }

        JsonObject current = doc["current_weather"];
        weatherInfoData.temperature = String((float)current["temperature"]);
        weatherInfoData.weathercode = current["weathercode"];

        http.end();
        return true;
    }

    Serial.println("HTTP失败");
    http.end();
    return false;
}

WeatherInfo weatherGet() {

    return weatherInfoData;
}