#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// Creating an object for the BME280 sensor..
Adafruit_BME280 bme;

void setup() {
  Serial.begin(9600);
  
  // Initialize I2C
  Wire.begin();

  // Initializing the BME280 sensor with address 0x77..
  if (!bme.begin(0x77)) {
    Serial.println("BME280 sensor not found!");
    while (1);
  }

  Serial.println("BME280 Sensor Initialized!");
}

void loop() {
  // We're writing the code to read temperature, pressure, and humidity data from the sensor..
  float temperature = bme.readTemperature();
  float pressure = bme.readPressure() / 100.0F; // Pressure in hPa.
  float humidity = bme.readHumidity();
  
 // Show the data on the serial monitor.
  Serial.print(temperature);
  Serial.print(pressure);
  Serial.print(humidity);

  // Wait for 2 seconds..
  delay(2000);
}
