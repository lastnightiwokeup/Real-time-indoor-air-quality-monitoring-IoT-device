#ifndef BUZZER_H
#define BUZZER_H

#define BUZZER_PIN 26

class Buzzer {
private:
  bool buzzerOn;
  unsigned long buzzerStartTime;
  unsigned int buzzerDuration;
  float minHumidity;
  float maxHumidity;

public:
  Buzzer(unsigned int duration, float minHum, float maxHum);
  void start();
  void stop();
  void update(float humidity);
  void pms7003Update(int pm2_5);
};

#endif