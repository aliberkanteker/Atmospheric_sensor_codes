#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
int verisayaci=1;

Adafruit_MPU6050 mpu;

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);


  Serial.print(a.acceleration.x); 
  Serial.print(a.acceleration.y); 
  Serial.println(a.acceleration.z);
  
  Serial.print(g.gyro.x);  
  Serial.print(g.gyro.y); 
  Serial.println(g.gyro.z);

  delay(1000); // veri ölçme aralığı
}
