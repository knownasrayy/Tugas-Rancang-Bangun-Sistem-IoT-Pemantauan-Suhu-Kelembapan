// KODE REVISI (LOGIKA DIBALIK)
// Pin Kabel Kuning masuk ke D15 ESP32

const int pinSensor = 15; 

void setup() {
  Serial.begin(115200);
  
  // Tetap gunakan INPUT_PULLUP
  pinMode(pinSensor, INPUT_PULLUP);
  
  Serial.println("--- MULAI MONITORING AIR (LOGIKA REVISI) ---");
  delay(1000);
}

void loop() {
  // Baca status pin (0 atau 1)
  int statusSensor = digitalRead(pinSensor);

  // Tampilkan angka mentah
  Serial.print("Angka Sensor: ");
  Serial.print(statusSensor);

  // LOGIKA BARU (DIBALIK)
  // Berdasarkan tes kamu:
  // 0 = Tidak ada apa-apa (Ground)
  // 1 = Ada tangan/Air (High/Pullup)
  
  if (statusSensor == HIGH) { // Ubah LOW jadi HIGH
    Serial.println("  --> 🌊 ADA AIR (Sensor Aktif)");
  } else {
    Serial.println("  --> ⛔ KERING (Sensor Mati)");
  }

  delay(500); 
}
