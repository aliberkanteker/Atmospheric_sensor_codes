#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_MPU6050.h>
#include <QMC5883LCompass.h>

Adafruit_BME280 bme;
Adafruit_MPU6050 mpu;
QMC5883LCompass compass;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  compass.init();
  Serial.println("QMC5883L Initialized...");

  if (!bme.begin(0x77)) {  // 0x76 or 0x77, depending on the sensor's address ..
  Serial.println("BME280 not found!");
  while (1);
  }

  // Initialize MPU6050 ..
  mpu.begin();
  if (!mpu.begin()) {
  Serial.println("MPU6050 not found!");
  while (1);
  }
}

void loop() {
  
int x, y, z;
float heading;

compass.read();

x = compass.getX();
y = compass.getY();
z = compass.getZ();
heading = compass.getAzimuth();

if (heading < 0) {
heading += 360;
}
sensors_event_t a, g, temp;
mpu.getEvent(&a, &g, &temp);

  
float temperature = bme.readTemperature();
float pressure = bme.readPressure()/100.0F;
float humidity = bme.readHumidity();


Serial.print("Acceleration   =  ");
Serial.print("X: ");
Serial.print(a.acceleration.x);
Serial.print("    , Y: "); 
Serial.print(a.acceleration.y);
Serial.print("     , Z: "); 
Serial.println(a.acceleration.z);

Serial.print("Gyroscope      =  ");
Serial.print("X: "); 
Serial.print(g.gyro.x);
Serial.print("     , Y: "); 
Serial.print(g.gyro.y);
Serial.print("     , Z: "); 
Serial.println(g.gyro.z);

Serial.print("Magnetic Field    = ");
Serial.print(" X: ");
Serial.print(x);
Serial.print("     , Y: ");
Serial.print(y);
Serial.print("     , Z: ");
Serial.println(z);  
Serial.print("Heading          =  ");
Serial.print(heading);
Serial.println("°");

delay(250);

Serial.print("BME280 Data  =  ");
Serial.print("T: ");
Serial.print(bme.readTemperature());
Serial.print("°C  ,");

Serial.print(" H: ");
Serial.print(bme.readHumidity());
Serial.print(" %  ,");

Serial.print(" P: ");
Serial.print(bme.readPressure() / 100.0F);
Serial.println(" hPa");

delay(1000);
}
