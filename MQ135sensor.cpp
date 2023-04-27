// Author: Connie Leung

#include "MQ135sensor.h"

void MQ135sensor::setupMQ135() {
  pinMode(this->digital_pin, INPUT);
  pinMode(this->analog_pin, INPUT);
}

void MQ135sensor::loopMQ135() {
  // Read analog and digital values from MQ-135 sensor
  this->airQuality = analogRead(this->analog_pin);
  this->MQ135digitalValue = digitalRead(this->digital_pin);
}

void MQ135sensor::printSerialMonitor() {
  Serial.print("Threshold: ");
  Serial.print(this->MQ135digitalValue);
  Serial.print(", ");
  Serial.print("Air quality: ");
  Serial.println(this->airQuality);
}

int MQ135sensor::getAnalog() {
  return this->airQuality;
}

int MQ135sensor::getDigital() {
  return this->MQ135digitalValue;
}
