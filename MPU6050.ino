#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

// Creating an object for the MPU6050 sensor ..
Adafruit_MPU6050 mpu;

void loop() { 
// Reading definitions to get axis data from the sensor ..
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  // We're printing data to the serial monitor...
  Serial.print(a.acceleration.x); 
  Serial.print(a.acceleration.y); 
  Serial.println(a.acceleration.z);
  
  Serial.print(g.gyro.x);  
  Serial.print(g.gyro.y); 
  Serial.println(g.gyro.z);

  delay(1000); // data measuring range ...
}
