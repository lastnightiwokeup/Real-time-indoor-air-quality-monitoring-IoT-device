#include "mySGP30.h"

MySGP30::MySGP30() {
}

bool MySGP30::begin() {
  Wire.begin();
  if (sgp30.begin() == false) {
    return false;
  }
  sgp30.initAirQuality();
  return true;
}

void MySGP30::measureAirQuality() {
  sgp30.measureAirQuality();
  CO2 = sgp30.CO2;
  TVOC = sgp30.TVOC;
}

void MySGP30::printSerialMonitor() {
  Serial.print("CO2: ");
  Serial.print(sgp30.CO2);
  Serial.print(" ppm\tTVOC: ");
  Serial.print(sgp30.TVOC);
  Serial.println(" ppb");
}

int MySGP30::getCO2() {
  return CO2;
}

int MySGP30::getTVOC() {
  return TVOC;
}
