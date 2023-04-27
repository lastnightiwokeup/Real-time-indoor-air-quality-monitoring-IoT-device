// Author: Connie Leung

#include "pms7003.h"

PMS7003::PMS7003(int rxPin, int txPin) : pms7003(rxPin, txPin), pm1(0), pm2_5(0), pm10(0) {}

void PMS7003::begin() {
  pms7003.begin(9600);
}

void PMS7003::read() {
  int index = 0;
  char value;
  char previousValue;

  // Read data from the sensor
  while (pms7003.available()) {
    value = pms7003.read();
    if ((index == 0 && value != 0x42) || (index == 1 && value != 0x4d)) {
      Serial.println("Cannot find the data header.");
      break;
    }

    if (index == 4 || index == 6 || index == 8 || index == 10 || index == 12 || index == 14) {
      previousValue = value;
    }
    else if (index == 5) {
      pm1 = 256 * previousValue + value;
    }
    else if (index == 7) {
      pm2_5 = 256 * previousValue + value;
    }
    else if (index == 9) {
      pm10 = 256 * previousValue + value;
    }
    else if (index > 15) {
      break;
    }
    index++;
  }
  while (pms7003.available()) pms7003.read();
}

void PMS7003::printSerialMonitor() {
  Serial.print("PM 1.0 (ug/m3): ");
  Serial.print(pm1);
  Serial.print(", ");
  Serial.print("PM 2.5 (ug/m3): ");
  Serial.print(pm2_5);
  Serial.print(", ");
  Serial.print("PM 10.0 (ug/m3): ");
  Serial.println(pm10);
}

int PMS7003::getPM1() {
  return pm1;
}

int PMS7003::getPM2_5() {
  return pm2_5;
}

int PMS7003::getPM10() {
  return pm10;
}
