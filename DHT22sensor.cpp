#include "DHT22sensor.h"

DHT22sensor::DHT22sensor(int pinNumber) : pin(pinNumber), dht(pinNumber, DHT22) {}

void DHT22sensor::begin() {
  dht.begin();
}

void DHT22sensor::readSensor() {
  humi = dht.readHumidity();
  tempC = dht.readTemperature();
  tempF = dht.readTemperature(true);
}

void DHT22sensor::printSerialMonitor() {
  Serial.print("Humidity:");
  Serial.print(humi, 0);
  Serial.print("%");
  Serial.print(" Temperature:");
  Serial.print(tempC, 1);
  Serial.print("C ~ ");
  Serial.print(tempF, 1);
  Serial.println("F"); 
}


float DHT22sensor::getHumidity() {
  return humi;
}

float DHT22sensor::getTemperatureC() {
  return tempC;
}

float DHT22sensor::getTemperatureF() {
  return tempF;
}
