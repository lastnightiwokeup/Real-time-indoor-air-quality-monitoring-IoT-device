#ifndef PMS7003_H
#define PMS7003_H

#include <SoftwareSerial.h>
#include "Arduino.h"

class PMS7003 {
  public:
    PMS7003(int rxPin, int txPin);
    void begin();
    void read();
    void printSerialMonitor();
    int getPM1();
    int getPM2_5();
    int getPM10();

  private:
    SoftwareSerial pms7003;
    int pm1;
    int pm2_5;
    int pm10;
};

#endif
