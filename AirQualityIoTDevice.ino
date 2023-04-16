// Import library of different sensors
#include "DHT22sensor.h"
#include "pms7003.h"
#include "MQ4sensor.h"
#include "MQ135sensor.h"
#include "MySGP30.h"
#include "Buzzer.h"
#include "OLED.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// Define pin numbers for different sernsors
#define DHTPin 25
#define DHTType DHT22
#define analog_pin 39
#define digital_pin 17
#define MQ4_LED_pin 13
#define MQ135_LED_pin 12
#define rxPin 14
#define txPin 27

#define BLYNK_TEMPLATE_ID "TMPL9PKM7FxB"
#define BLYNK_TEMPLATE_NAME "Air Quality IoT Device"

char auth[] = "9EvktN40KlCG3HOjOUeZcgKQx5Fmu43A";
char ssid[] = "Chisinb";
char pass[] = "32145577";

BlynkTimer timer;

//Initializing objects of different classes for various sensors
DHT22sensor dht22(DHTPin);
PMS7003 pms7003(rxPin, txPin);
Buzzer buzzer(500, 30, 70); //Set duration to 500ms, and min/max humidity range
MQ4sensor mq4sensor;
MQ135sensor mq135sensor;
MySGP30 sgp30;
OLED oled;

// Declare global variables
float humi = 0;
float tempC = 0;
float tempF = 0;
int CO2 = 0;
int TVOC = 0;
int sensorValue = 0;
int digitalValue = 0;
int airQuality = 0;
int MQ135digitalValue = 0; 
int pm1 = 0;
int pm2_5 = 0;
int pm10 = 0;

// This function sends Arduino's up time every second to different Virtual Pins
void sensorDataSend()
{
  Blynk.virtualWrite(V1, pm1);
  Blynk.virtualWrite(V2, pm2_5);
  Blynk.virtualWrite(V3, pm10);
  Blynk.virtualWrite(V0, tempC);
  Blynk.virtualWrite(V4, humi);
  Blynk.virtualWrite(V5, tempF);
  Blynk.virtualWrite(V6, CO2);
  Blynk.virtualWrite(V7, TVOC);
  Blynk.virtualWrite(V8, airQuality);
  Blynk.virtualWrite(V9, sensorValue);  
}

void setup() {
  Serial.begin(9600);
  dht22.begin();
  mq4sensor.setupMQ4();
  mq135sensor.setupMQ135();
  sgp30.begin();
  pms7003.begin();
  oled.begin();

  // Connect to WiFi network
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  // Connect to Blynk server
  Blynk.begin(auth, ssid, pass);

  // Timer will run every sec 
  timer.setInterval(1000L, sensorDataSend);
}

void loop() {
  updateSensorData();
  updateOledDisplay();
  buzzerUpdate();
  logBlynkEvent();
  Blynk.run();
  timer.run();
}

void updateSensorData() {
  // Read sensor data and update variables
  dht22.readSensor();
  dht22.printSerialMonitor();
  delay(1000);
  humi = dht22.getHumidity();
  tempC = dht22.getTemperatureC();
  tempF = dht22.getTemperatureF();
  
  pms7003.read();
  pms7003.printSerialMonitor();
  delay(1000);
  pm1 = pms7003.getPM1();
  pm2_5 = pms7003.getPM2_5();
  pm10 = pms7003.getPM10();
  
  sgp30.measureAirQuality();
  sgp30.printSerialMonitor();
  delay(1000);
  CO2 = sgp30.getCO2();
  TVOC = sgp30.getTVOC();
  
  mq4sensor.loopMQ4();
  mq4sensor.printSerialMonitor();
  delay(1000);
  sensorValue = mq4sensor.getAnalog();
  digitalValue = mq4sensor.getDigital();
  
  mq135sensor.loopMQ135();
  mq135sensor.printSerialMonitor();
  delay(1000);
  airQuality = mq135sensor.getAnalog();
  MQ135digitalValue = mq135sensor.getDigital();
}

void updateOledDisplay() {
  static int oledState = 0;
  static unsigned long previousMillis = 0;
  const unsigned long interval = 500; // Delay of 1 second

  unsigned long currentMillis = millis();

  switch(oledState) {
    case 0:
      if (currentMillis - previousMillis >= interval) {
        oled.clear();
        oled.DHT22oledDisplayHeader();
        oled.DHT22oledDisplay(3, 5, 28, humi, "%");
        oled.DHT22oledDisplay(2, 70, 16, tempC, "C");
        oled.DHT22oledDisplay(2, 70, 44, tempF, "F");
        oled.show();
        oledState++;
        previousMillis = currentMillis;
      }
      break;
    case 1:
      if (currentMillis - previousMillis >= interval) {
        oled.clear();
        oled.displayCH4(sensorValue, MQ4_LED_pin);
        oled.show();
        oledState++;
        previousMillis = currentMillis;
      }
      break;
    case 2:
      if (currentMillis - previousMillis >= interval) {
        oled.clear();
        oled.displayAirQuality(airQuality, MQ135_LED_pin);
        oled.show();
        oledState++;
        previousMillis = currentMillis;
      }
      break;
    case 3:
      if (currentMillis - previousMillis >= interval) {
        oled.clear();
        oled.displayCO2andTVOC(CO2, TVOC);
        oled.show();
        oledState++;
        previousMillis = currentMillis;
      }
      break;
    case 4:
      if (currentMillis - previousMillis >= interval) {
        oled.clear();
        oled.displayParticulates(pm1, pm2_5, pm10);
        oled.show();
        oledState = 0;
        previousMillis = currentMillis;
      }
      break;
  }
}

void buzzerUpdate() {
  buzzer.update(humi); 
  buzzer.pms7003Update(pm2_5);
}

void logBlynkEvent() {
  // Log event to Blynk server
  // Show warning messages to users
  if (humi > 65) {
    Blynk.logEvent("humidity_alert", String("Humidity is over 65%!")); 
  }

  if (CO2>1000) {                                              
    Blynk.logEvent("co2_alert", String("High CO2 Detected!"));     
  }

   if (sensorValue > 500) {
    Blynk.logEvent("methane_alert", String("Methane concentration is too HIGH!"));
   }

   if (airQuality > 400) {
    Blynk.logEvent("airquality_alert", String("The air quality is BAD!"));
   }

   if (pm2_5 > 35) {
    Blynk.logEvent("pm25_alert", String("PM2.5 is too HIGH!")); 
  }
} 