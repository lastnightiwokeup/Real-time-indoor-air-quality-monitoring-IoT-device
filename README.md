# Arduino-Air-Quality-IoT-Device

This is a real time Air Quality IoT Device that connects to Blynk.

AirQualityIoTDevice.ino : Integrate all the sensors as a whole IoT device

Those .h and .cpp files are used to organize code into reusable libraries or modules. 
The .h file is the header file that contains declarations of functions, variables, and constants that are used by the library.

While the .cpp file is the implementation file that contains the actual code for the functions declared in the header file.

Specification
Sensor:
DHT22   : Temperature and Humidity
SGP30   : Carbon Dioxide and Volatile Organic Compounds
MQ-4    : Methane
MQ-135  : Overall air quality
PMS7003 : Particulates (PM1, PM2.5, PM10)

Microcontroller ： ESP32
OLED Display : SSD1306

IoT Platform : Blynk
IDE : Arduino
