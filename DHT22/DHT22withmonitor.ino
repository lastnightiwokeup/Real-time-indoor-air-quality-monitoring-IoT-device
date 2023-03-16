//import required libraries
//For DHT22
#include "DHT.h"
#define DHTPin 25
#define DHTType DHT22
//For SSD1306
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//Declare varaible for humidity, temperature in Celsius and Fahrenheit
DHT HT(DHTPin, DHTType);
float humi;
float tempC;
float tempF;

//OLED define
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(9600);
  HT.begin();
  //For OLED I2C
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
}

void loop() {
  delay(1000);
  humi = HT.readHumidity();
  tempC = HT.readTemperature();
  tempF = HT.readTemperature(true);

  Serial.print("Humidity:");
  Serial.print(humi, 0);
  Serial.print("%");
  Serial.print(" Temperature:");
  Serial.print(tempC, 1);
  Serial.print("C ~ ");
  Serial.print(tempF, 1);
  Serial.println("F");

  display.clearDisplay();
  oledDisplayHeader();


  oledDisplay(3, 5, 28, humi, "%");
  oledDisplay(2, 70, 16, tempC, "C");
  oledDisplay(2, 70, 44, tempF, "F");

  display.display();

}
void oledDisplayHeader() {
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Humidity");
  display.setCursor(60, 0);
  display.print("Temperature");
}
void oledDisplay(int size, int x, int y, float value, String unit) {
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