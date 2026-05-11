#ifndef WEATHER_H
#define WEATHER_H

#include <Arduino.h>

struct WeatherInfo {

    String temperature;

    int weathercode;
};

void weatherInit();

bool weatherUpdate();

WeatherInfo weatherGet();

#endif