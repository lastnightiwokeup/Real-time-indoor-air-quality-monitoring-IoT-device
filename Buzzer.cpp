// Author: Connie Leung
#include "Buzzer.h"
#include "Arduino.h"

Buzzer::Buzzer(unsigned int duration, float minHum, float maxHum) {
  buzzerOn = false;
  buzzerStartTime = 0;
  buzzerDuration = duration;
  minHumidity = 50;
  maxHumidity = 70;
  pinMode(BUZZER_PIN, OUTPUT);
}

void Buzzer::start() {
  tone(BUZZER_PIN, 1000); //1000 Hz frequency
  buzzerOn = true;
  buzzerStartTime = millis(); //Start counting time
}

void Buzzer::stop() {
  noTone(BUZZER_PIN);
  buzzerOn = false;
}

void Buzzer::update(float humidity) {
  //Check if humidity is outside desired range
  if (humidity < minHumidity || humidity > maxHumidity) {
    //Check if buzzer is not already on
    if (!buzzerOn) {
      start();
    } else {
      //Check if buzzer has been on for more than buzzerDuration milliseconds
      if (millis() - buzzerStartTime > buzzerDuration) {
        stop();
      }
    }
  } else {
    //If humidity is within desired range, turn off buzzer if it was on
    if (buzzerOn) {
      stop();
    }
  }
}

void Buzzer::pms7003Update(int pm2_5) {
  if (pm2_5 > 35) {
    // Sounds the buzzer at the frequency relative to the note C in Hz
    tone(BUZZER_PIN, 261); 
    delay(200);
    //Turns the buzzer off
    noTone(BUZZER_PIN);
  } 
}
