/*   
PM2.5 => Particles with a diameter of 2.5 micrometers or less. They are so small that they can reach deep into the lungs and even enter the bloodstream.
PM10 => Particles with a diameter of 10 micrometers or less. They are larger and are usually trapped in the nose and throat. They come from sources such as construction dust, soil particles, and pollen.
*/

#include <SoftwareSerial.h>

// SoftwareSerial connection for SDS011 (RX=2, TX=3) ..
SoftwareSerial SDS011Serial(2, 3);

uint8_t buffer[10]; 
float PM25, PM10; // PM2.5 and PM10 values (as float) ..
void setup() {
  Serial.begin(9600);
  SDS011Serial.begin(9600);
  Serial.println("SDS011 PM Sensor Initialized.");
}

void loop() {
  if (readSDS011()) { 
    // Calculate PM2.5 and PM10 values ..
    PM25 = ((buffer[3] << 8) + buffer[2]) / 10.0;
    PM10 = ((buffer[5] << 8) + buffer[4]) / 10.0;

    // Print to serial monitor ..
    Serial.print("PM2.5: ");
    Serial.print(PM25, 1); // 1 decimal place ..
    Serial.print(" µg/m³, PM10: ");
    Serial.print(PM10, 1);
    Serial.println(" µg/m³");
  }

  delay(1000); // SDS011 already sends 1 Hz data, so wait 1 second ..
}

// SDS011 data reading function ..
bool readSDS011() {
  if (SDS011Serial.available() >= 10) {
    // Wait until the header (0xAA) is found ..
    while (SDS011Serial.read() != 0xAA) {
      if (!SDS011Serial.available()) return false;
    }

    buffer[0] = 0xAA;
    for (int i = 1; i < 10; i++) {
      buffer[i] = SDS011Serial.read();
    }

    // Packet end (0xAB) check ..
    if (buffer[9] == 0xAB) {
      // calculate checksum ..
      uint8_t checksum = 0;
      for (int i = 2; i < 8; i++) checksum += buffer[i];

      if (checksum == buffer[8]) {
        return true; // Successful reading ..
      }
    }
  }
  return false;
}
