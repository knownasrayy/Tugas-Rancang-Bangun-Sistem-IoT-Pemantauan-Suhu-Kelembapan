// ==========================================
// PIN KABEL
// ==========================================
const int pinSensor = 15; // Kabel Kuning Sensor
const int pinBuzzer = 18; // Kaki Panjang (+) Buzzer

unsigned long lastMsg = 0;

void setup() {
  // Memulai Serial Monitor untuk pemantauan
  Serial.begin(115200);
  
  // Setup Pin
  pinMode(pinSensor, INPUT_PULLUP); // Menggunakan Pullup Internal
  pinMode(pinBuzzer, OUTPUT);
  
  // Pastikan Buzzer Mati saat alat pertama kali dinyalakan
  digitalWrite(pinBuzzer, LOW); 
  
  Serial.println("--- Sistem Monitoring Galon (Offline) Ready ---");
}

void loop() {
  // --- 1. PEMBACAAN SENSOR (REAL-TIME) ---
  int sensorState = digitalRead(pinSensor);

  // --- 2. LOGIKA BUZZER ---
  // Jika sensor HIGH (Kering/Habis), Buzzer NYALA.
  // Jika sensor LOW (Ada Air), Buzzer MATI.
  if (sensorState == HIGH) { 
    digitalWrite(pinBuzzer, HIGH); // NYALA
  } 
  else { 
    digitalWrite(pinBuzzer, LOW);  // MATI
  }

  // --- 3. TAMPILAN STATUS KE SERIAL MONITOR (TIAP 2 DETIK) ---
  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    
    if (sensorState == LOW) {
      Serial.println("Status: AMAN (Air Ada) 🌊");
    } else {
      Serial.println("Status: BAHAYA (Air Habis!) ⛔");
    }
  }
}
