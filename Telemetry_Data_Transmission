#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_HMC5883_U.h>
#include <Adafruit_MPU6050.h>
#include <ArduinoJson.h>

Adafruit_BME280 bme;
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
Adafruit_MPU6050 mpu;

void setup() {
    Serial.begin(57600); // Serial connection for RF900 ..
    Wire.begin();

    // Initializing the sensors ..
    if (!bme.begin(0x77)) {
        Serial.println("BME280 not found!");
        while (1);
    }

    if (!mag.begin()) {
        Serial.println("HMC5883L not found!");
        while (1);
    }

    mpu.begin();
}

void loop() {
    // Get sensor data ..
    float temperature = bme.readTemperature();
    float humidity = bme.readHumidity();
    float pressure = bme.readPressure() / 100.0F;

    // Magnetic field data ..
    sensors_event_t event;
    mag.getEvent(&event);
    float heading = atan2(event.magnetic.y, event.magnetic.x) * 180 / PI;

    // MPU6050 sensor data (accel and gyro data) ..
    sensors_event_t a,g,temp;
    mpu.getEvent(&a,&g,&temp); //

    // Convert data to JSON format ..
    StaticJsonDocument<256> doc;
    doc["Temperature"] = temperature;
    doc["Humidity"] = humidity;
    doc["Pressure"] = pressure;
    doc["Heading"] = heading;
    doc["Accel_X"] = a.acceleration.x;
    doc["Accel_Y"] = a.acceleration.y;
    doc["Accel_Z"] = a.acceleration.z;
    doc["Gyro_X"] = g.gyro.x;
    doc["Gyro_Y"] = g.gyro.y;
    doc["Gyro_Z"] = g.gyro.z;

    // Send JSON data ..
    serializeJson(doc, Serial);
    Serial.println(); // Print the sent data to the serial monitor

    delay(1000);
}
