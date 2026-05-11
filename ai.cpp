#include "ai.h"
#include "weather.h"
#include "mydht.h"
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
static String lastAIAdvice = "AI Ready";
static unsigned long lastAIUpdate = 0;
String queryAI(String prompt) {
    if (prompt == "weather") {
        float t = getTemperature();
        float h = getHumidity();
        int code = weatherGet().weathercode;
        String base = String(t,0) + "C " + String(h,0) + "% | ";
        String advice = "";

        // 优先尝试真实API
        WiFiClient client;
        HTTPClient http;
        http.begin(client, "http://api.adviceslip.com/advice");
        http.setTimeout(2000);

        if (http.GET() == HTTP_CODE_OK) {
            String payload = http.getString();
            DynamicJsonDocument doc(1024);
            if (!deserializeJson(doc, payload)) {
                advice = doc["slip"]["advice"].as<String>().substring(0, 35);
            }
        }
        http.end();

        // 确保永远有具体语句（新增默认分支覆盖code=-1等情况）
        if (advice.length() < 3) {
            if (code == 0) advice = "Sunny, good to go out";
else if (code == 1 || code == 2 || code == 3) advice = "Cloudy, nice day";
else if (code >= 51 && code <= 67) advice = "Rainy, bring umbrella";
else if (code >= 45 && code <= 48) advice = "Foggy, drive safe";
else advice = "Weather OK, stay safe";
        }

        return base + advice;
    }
    return "AI Ready";
}