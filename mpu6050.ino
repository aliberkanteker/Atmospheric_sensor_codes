#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
int verisayaci=1;

Adafruit_MPU6050 mpu;

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print(verisayaci);
  Serial.println(".Veri");

  Serial.print("İvmeölçer = ");
  Serial.print(" X :");
  Serial.print(a.acceleration.x); 
  Serial.print(" , Y : ");
  Serial.print(a.acceleration.y); 
  Serial.print(" , Z : "); 
  Serial.println(a.acceleration.z);

  Serial.print("Jiroskop  = ");
  Serial.print(" X :");
  Serial.print(g.gyro.x); 
  Serial.print(" , Y : "); 
  Serial.print(g.gyro.y); 
  Serial.print(" , Z : "); 
  Serial.println(g.gyro.z);

  Serial.print("Sıcaklık  =  "); 
  Serial.print(temp.temperature); 
  Serial.println(" °C");
  delay(1000); // veri ölçme aralığı
}
