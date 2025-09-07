#include <Wire.h>
#include <QMC5883LCompass.h> //We need to upload this library because we're using the clone model of the HMC5883L here ..

QMC5883LCompass compass;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  compass.init();  // Initialize the sensor ..
}

void loop() {
  int x, y, z;
  float heading;

  //We're reading X, Y, Z, and heading data from the sensor..
  compass.read();
  
  // The definitions we use to get X, Y, Z, and heading data.
  x = compass.getX();
  y = compass.getY();
  z = compass.getZ();
  heading=compass.getAzimuth();

if (heading < 0) {
  heading+=360;
}

  // We're printing the data to the serial monitor.
  Serial.print(x);
  Serial.print(y);
  Serial.println(z);
  Serial.println(heading);
  delay(1000); // data measuring range ...
}
