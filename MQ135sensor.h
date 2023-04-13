#ifndef MQ135SENSOR_H
#define MQ135SENSOR_H

#include "Arduino.h"

class MQ135sensor {
  public:
    void setupMQ135();
    void loopMQ135();
    int getAnalog();
    int getDigital();
    void printSerialMonitor();
    
  private:
    int airQuality;
    int MQ135digitalValue;
    int analog_pin = 34;
    int digital_pin = 16;
};

#endif
