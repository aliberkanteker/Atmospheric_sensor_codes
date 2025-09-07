#include <Wire.h>
#include <QMC5883LCompass.h> //Burada HMC5883L'nin klon modelini kullandığımız için bu kütüphaneyi yüklememiz gerekiyor..

QMC5883LCompass compass;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  compass.init();  // Sensörü başlat ..
}

void loop() {
  int x, y, z;
  float heading;

  // Sensörden X, Y, Z ve heading verilerini okutuyoruz..
  compass.read();
  
  // X, Y, Z ve heading verilerini almak için kullandığımız tanımlamalar..
  x = compass.getX();
  y = compass.getY();
  z = compass.getZ();
  heading=compass.getAzimuth();

if (heading < 0) {
  heading+=360;
}

  // Seri monitörde verileri yazdırıyoruz..
  Serial.print(x);
  Serial.print(y);
  Serial.println(z);
  Serial.println(heading);
  delay(1000);
}
