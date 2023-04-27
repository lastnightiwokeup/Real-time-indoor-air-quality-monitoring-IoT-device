// Author: Connie Leung

#ifndef DHT22SENSOR_H
#define DHT22SENSOR_H

#include <DHT.h>

class DHT22sensor {
  public:
    DHT22sensor(int pinNumber);
    void begin();
    void readSensor();
    void printSerialMonitor();
    float getHumidity();
    float getTemperatureC();
    float getTemperatureF();

  private:
    int pin;
    DHT dht;
    float humi;
    float tempC;
    float tempF;
};

#endif
