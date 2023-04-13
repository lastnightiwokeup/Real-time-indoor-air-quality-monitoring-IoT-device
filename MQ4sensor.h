#ifndef MQ4SENSOR_H
#define MQ4SENSOR_H

#include "Arduino.h"

class MQ4sensor {
  public:
    void setupMQ4();
    void loopMQ4();
    int getAnalog();
    int getDigital();
    void printSerialMonitor();

  private:
    int sensorValue;
    int digitalValue;
    int analog_pin = 39;
    int digital_pin = 17;
};

#endif
