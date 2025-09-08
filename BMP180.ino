#include <Adafruit_BMP085.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>

Adafruit_BMP085 bmp;


void setup() {
  Serial.begin(9600); // Start serial communication ..

  // Define the appropriate SDA and SCL pins for I2C communication .. 
  Wire.begin(21, 22); // On ESP32, defined SDA = 21, SCL = 22

  // Initialize the BMP180 sensor ..
  if (!bmp.begin()) {
    Serial.println("BMP180 sensor not found!");
    while (1);
  }

  Serial.println("BMP180 Sensor Initialized!");
}

void loop() {
  float temperature = bmp.readTemperature();
  float pressure = bmp.readPressure()/100.0F;
  
  // Print temperature and pressure values ..
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print(pressure);
  Serial.println(" hPa");
  
  delay(2000); // wait for 2 second
}
