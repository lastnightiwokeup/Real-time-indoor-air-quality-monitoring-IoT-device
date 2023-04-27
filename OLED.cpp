// Author: Connie Leung

#include "OLED.h"
const int MQ4_LED_pin = 13;
const int MQ135_LED_pin = 12;
const int LEDC_CHANNEL = 0;
OLED::OLED() : display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1) {}

void OLED::begin() {
if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
Serial.println(F("SSD1306 allocation failed"));
for (;;);
}
ledcSetup(LEDC_CHANNEL, 1000, 8);
  // Attach LEDC channel to the LED pin
ledcAttachPin(MQ135_LED_pin, LEDC_CHANNEL);
ledcAttachPin(MQ4_LED_pin, LEDC_CHANNEL);
pinMode(MQ135_LED_pin, OUTPUT); 
pinMode(MQ4_LED_pin, OUTPUT); 
}

void OLED::clear() {
display.clearDisplay();
}

void OLED::show() {
display.display();
}

void OLED::DHT22oledDisplayHeader() {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Humidity");
  display.setCursor(60, 0);
  display.print("Temperature");
}

void OLED::DHT22oledDisplay(int size, int x, int y, float value, String unit) {
  int charLen = 12;
  int xo = x + charLen * 3.2;
  int xunit = x + charLen * 3.6;
  int xval = x;
  display.setTextSize(size);
  display.setTextColor(WHITE);

  if (unit == "%") {
    display.setCursor(x, y);
    display.print(value, 0);
    display.print(unit);
  } else {
    if (value > 99) {
      xval = x;
    } else {
      xval = x + charLen;
    }
    display.setCursor(xval, y);
    display.print(value, 0);
    display.drawCircle(xo, y + 2, 2, WHITE); // print degree symbols (  )
    display.setCursor(xunit, y);
    display.print(unit);
  }
}

void OLED::displayCH4(int sensorValue, int MQ4_LED_pin) {
  // Display "CH4:" and methane concentration
  display.setTextSize(2);
  display.setCursor(0, 0);
  display.print("CH4:");
  display.setTextSize(2);
  display.setCursor(0, 25);
  display.print(sensorValue);
  display.print(" ppm");

   //Check if ppm value is greater than 1000
  if (sensorValue > 1000) {
    digitalWrite(MQ4_LED_pin, HIGH);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 45);
    display.print("HIGH ALERT");
  }
  else {
    digitalWrite(MQ4_LED_pin, LOW);
  }
}

void OLED::displayAirQuality(int airQuality, int MQ135_LED_pin) {
 // Display "Air Quality:" and pollutant concentration
  display.setTextSize(1.5);
  display.setCursor(0, 0);
  display.print("Air Quality:");
  display.setTextSize(2);
  display.setCursor(0, 20);
  display.print(airQuality);
  display.print(" ppm");

  //Check if ppm value is greater than 400
  if (airQuality > 400) {
    digitalWrite(MQ135_LED_pin, HIGH);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0, 40);
    display.print("HIGH ALERT");
  }
  else {
    digitalWrite(MQ135_LED_pin, LOW);
  }
}

void OLED::displayCO2andTVOC (int CO2, int TVOC) {
  // Set the cursor position for the CO2 reading on the OLED display
  display.setCursor(0, 10); 
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("CO2:");
  display.print(CO2);
  display.setTextSize(1);
  display.print("ppm");
 
  // Set the cursor position for the TVOC reading on the OLED display
  display.setCursor(0, 40); 
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.print("TVOC:");
  display.print(TVOC);
  display.setTextSize(1);
  display.print("ppb");
}

void OLED::displayParticulates(int pm1, int pm2_5, int pm10) {
  display.clearDisplay(); display.setTextColor(WHITE);
  display.drawRoundRect(0, 0, 127, 40, 3, WHITE); 
  display.drawRoundRect(0, 40, 60, 23, 3, WHITE); 
  display.drawRoundRect(60, 40, 66, 23, 3, WHITE);
  display.setCursor(85, 10); 
  display.setTextSize(1); 
  display.println("PM2.5"); 
  display.setCursor(85, 25); 
  display.println("ug/m"); 
  display.setCursor(108, 22); 
  display.println("3");
  display.setCursor(20, 10); 
  display.setTextSize(3); 
  display.print(pm2_5);
  display.setCursor(4, 47); 
  display.setTextSize(1); 
  display.print("PM1 : "); 
  display.print(pm1);
  display.setCursor(64, 47); 
  display.setTextSize(1); 
  display.print("PM10 : "); 
  display.print(pm1);
  display.display();
}
