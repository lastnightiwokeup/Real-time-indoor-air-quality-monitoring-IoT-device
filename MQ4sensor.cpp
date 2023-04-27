// Author: Connie Leung

#include "MQ4sensor.h"

void MQ4sensor::setupMQ4() {
  pinMode(this->digital_pin, INPUT);
  pinMode(this->analog_pin, INPUT);
}

void MQ4sensor::loopMQ4() {
  // Read analog and digital values from MQ-4 sensor
  this->sensorValue = analogRead(this->analog_pin);
  this->digitalValue = digitalRead(this->digital_pin);
}

void MQ4sensor::printSerialMonitor() {
  Serial.print("Threshold: ");
  Serial.print(this->digitalValue);
  Serial.print(", ");
  Serial.print("Methane Concentration: ");
  Serial.println(this->sensorValue);
}

int MQ4sensor::getAnalog() {
  return this->sensorValue;
}

int MQ4sensor::getDigital() {
  return this->digitalValue;
}
