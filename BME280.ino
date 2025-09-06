#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

void loop() {

  // Sensörden sıcaklık, basınç ve nem verilerini okuması için kodu yazıyoruz.
  float temperature = bme.readTemperature();
  float pressure = bme.readPressure() / 100.0F; // Basınç hPa olarak
  float humidity = bme.readHumidity();

}
