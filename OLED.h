// Author: Connie Leung

#ifndef OLED_H
#define OLED_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Arduino.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

class OLED {
  public:
    OLED();
    void begin();
    void clear();
    void show();
    void DHT22oledDisplayHeader();
    void DHT22oledDisplay(int size, int x, int y, float value, String unit);
    void displayCH4(int sensorValue, int MQ4_LED_pin);
    void displayAirQuality(int airQuality, int MQ135_LED_pin);
    void displayCO2andTVOC(int CO2, int TVOC);
    void displayParticulates(int pm1, int pm2_5, int pm10);

  private:
    Adafruit_SSD1306 display;
};

#endif
