#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

// GPS object
TinyGPSPlus gps;

#define GPS_SERIAL Serial2 // GPS module ..
#define PC_SERIAL Serial // Communication with the computer (via USB) ..

unsigned long lastUpdateTime = 0;
const unsigned long UPDATE_INTERVAL = 5000;

void setup() {
  PC_SERIAL.begin(9600); //To send data to the computer ..
  GPS_SERIAL.begin(9600); // For communication with the GPS module ..
  PC_SERIAL.println("System is starting...");
  delay(2000);
}

void loop() {
// Reading data from the GPS ..
  while (GPS_SERIAL.available() > 0) {
    gps.encode(GPS_SERIAL.read()); // Process GPS data..
  }

  if (millis() - lastUpdateTime > UPDATE_INTERVAL) {
    displayGPSData();
    lastUpdateTime = millis();
  }
}

void displayGPSData() {
  PC_SERIAL.println("---------- GPS Data ----------");

  // Location data
  if (gps.location.isValid()) {
    PC_SERIAL.print(" Latitude: "); PC_SERIAL.print(gps.location.lat(), 6);
    PC_SERIAL.print(" | Longitude: "); PC_SERIAL.println(gps.location.lng(), 6);
  } else {
    PC_SERIAL.println("Location data is not valid !");
  }

  // Date and Time ...
  if (gps.date.isValid() && gps.time.isValid()) {
    PC_SERIAL.print(" Date: ");
    PC_SERIAL.print(gps.date.day()); PC_SERIAL.print("/");
    PC_SERIAL.print(gps.date.month()); PC_SERIAL.print("/");
    PC_SERIAL.println(gps.date.year());

    PC_SERIAL.print(" Time: ");
    PC_SERIAL.print(gps.time.hour()); PC_SERIAL.print(":");
    PC_SERIAL.print(gps.time.minute()); PC_SERIAL.print(":");
    PC_SERIAL.println(gps.time.second());
  } else {
    PC_SERIAL.println(" Date and time data is not valid ! ");
  }

  // Altitude ..
  if (gps.altitude.isValid()) {
    PC_SERIAL.print("Altitude: ");
    PC_SERIAL.print(gps.altitude.meters());
    PC_SERIAL.println(" m");
  }

  // Speed ..
  if (gps.speed.isValid()) {
    PC_SERIAL.print("Speed: ");
    PC_SERIAL.print(gps.speed.kmph());
    PC_SERIAL.println(" km/s");
  }

  // Direction ..
  if (gps.course.isValid()) {
    PC_SERIAL.print("Direction: ");
    PC_SERIAL.print(gps.course.deg());
    PC_SERIAL.println("°");
  }

  // Number of Satellites ..
  if (gps.satellites.isValid()) {
    PC_SERIAL.print("Number of Satellites: ");
    PC_SERIAL.println(gps.satellites.value());
  }

  // Horizontal Dilution of Precision (HDOP) ..
  if (gps.hdop.isValid()) {
    PC_SERIAL.print("📶 HDOP: ");
    PC_SERIAL.println(gps.hdop.hdop());
  }

  PC_SERIAL.println("-------------------------------------\n");
}
