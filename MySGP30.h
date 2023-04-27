// Author: Connie Leung

#ifndef MY_SGP30_H
#define MY_SGP30_H

#include "SparkFun_SGP30_Arduino_Library.h"
#include "Arduino.h"

class MySGP30 {
  public:
    MySGP30();
    bool begin();
    void measureAirQuality();
    void printSerialMonitor();
    int getCO2();
    int getTVOC();
    
  private:
    SGP30 sgp30;
    int CO2;
    int TVOC;
};

#endif
