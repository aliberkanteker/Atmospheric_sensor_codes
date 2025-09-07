#include <TinyGPS++.h>
#include <SoftwareSerial.h>

// TinyGPS++ nesnesini ekledik
TinyGPSPlus gps;

// Seri port tanımlamaları
#define GPS_SERIAL Serial1 // GPS modülü 
#define PC_SERIAL Serial   // Bilgisayarla iletişim (USB üzerinden)

// Değişkenler
unsigned long lastUpdateTime = 0; // Zamanlayıcı (bilgi akışı için için)

void setup() {   //Burada 2 farklı seri bağlantı balatıyoruz ..
  // Seri bağlantıları başlat
  PC_SERIAL.begin(9600);       // Bilgisayara bilgi göndermek için
  GPS_SERIAL.begin(9600);      // GPS modülüyle iletişim için
  PC_SERIAL.println("Sistem başlatılıyor...");
  PC_SERIAL.println("GPS modülü ile bağlantı kuruluyor...");
  delay(2000); // Başlangıç için kısa bir bekleme süresi
}

void loop() {
  // GPS'ten veri okuma
  while (GPS_SERIAL.available() > 0) {
    char c = GPS_SERIAL.read(); // Seri porttan bir karakter oku
    if (gps.encode(c)) {        // GPS verilerini çözümle
      displayGPSData();         // Çözümlemeden sonra bilgileri göster
    }
  }

  // Her 5 saniyede bir durum bilgisi göster
  if (millis() - lastUpdateTime > 5000) {
    showStatus();
    lastUpdateTime = millis();
  }
}

// GPS verilerini seri monitörde göster
void displayGPSData() {
  PC_SERIAL.println("---------- GPS Verileri ----------");
  
  if (gps.location.isValid()) {
    PC_SERIAL.print("Enlem: ");
    PC_SERIAL.print(gps.location.lat(), 6);
    PC_SERIAL.print(" | Boylam: ");
    PC_SERIAL.println(gps.location.lng(), 6);
  } else {
    PC_SERIAL.println("Konum bilgisi geçerli değil.");
  }

  if (gps.date.isValid() && gps.time.isValid()) {
    PC_SERIAL.print("Tarih: ");
    PC_SERIAL.print(gps.date.day());
    PC_SERIAL.print("/");
    PC_SERIAL.print(gps.date.month());
    PC_SERIAL.print("/");
    PC_SERIAL.println(gps.date.year());

    PC_SERIAL.print("Saat: ");
    PC_SERIAL.print(gps.time.hour());
    PC_SERIAL.print(":");
    PC_SERIAL.print(gps.time.minute());
    PC_SERIAL.print(":");
    PC_SERIAL.println(gps.time.second());
  } else {
    PC_SERIAL.println("Tarih ve saat bilgisi geçerli değil.");
  }
  
  PC_SERIAL.println("----------------------------------");
}

// GPS modülü durumu hakkında bilgi ver
void showStatus() {
  PC_SERIAL.println("---------- Durum Bilgisi ----------");
  
  if (gps.charsProcessed() > 0) {
    PC_SERIAL.println("GPS verisi alınmaya devam ediyor...");
    PC_SERIAL.print("Toplam işlenen karakter: ");
    PC_SERIAL.println(gps.charsProcessed());
  } else {
    PC_SERIAL.println("GPS verisi alınamıyor. Lütfen bağlantıları kontrol edin!");
  }

  if (gps.satellites.isValid()) {
    PC_SERIAL.print("Uydu Sayısı: ");
    PC_SERIAL.println(gps.satellites.value());
  } else {
    PC_SERIAL.println("Uydu bilgisi alınamadı.");
  }
  
  PC_SERIAL.println("----------------------------------");
}
