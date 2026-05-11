#ifndef WIFI_H
#define WIFI_H

#include <Arduino.h>
#include <ESP8266WiFi.h>

#define WIFI_SSID "小米13"
#define WIFI_PASSWORD "00000000"

void wifiInit();
bool wifiConnect(const char* ssid = WIFI_SSID, const char* password = WIFI_PASSWORD);

#endif