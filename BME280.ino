#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

// BME280 sensörü için nesne oluşturuyoruz
Adafruit_BME280 bme;

void setup() {
  Serial.begin(9600);
  
  // I2C başlatma
  Wire.begin();

  // BME280 sensörünü 0x77 adresiyle başlatıyoruz
  if (!bme.begin(0x77)) {
    Serial.println("BME280 sensörü bulunamadı!");
    while (1);
  }

  Serial.println("BME280 Sensörü Başlatıldı!");
}

void loop() {
  // Sensörden sıcaklık, basınç ve nem verilerini okuması için kodu yazıyoruz.
  float temperature = bme.readTemperature();
  float pressure = bme.readPressure() / 100.0F; // Basınç hPa olarak
  float humidity = bme.readHumidity();
  
 // Seri monitörde verileri göster 
  Serial.print(temperature);
  Serial.print(pressure);
  Serial.print(humidity);

  // 2 saniye bekle
  delay(2000);
}
