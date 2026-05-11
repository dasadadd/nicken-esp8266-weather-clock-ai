#include "mydht.h"
#include <DHT.h>

#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void dhtInit() {
    dht.begin();
}

float getTemperature() {
    return dht.readTemperature();
}

float getHumidity() {
    return dht.readHumidity();
}