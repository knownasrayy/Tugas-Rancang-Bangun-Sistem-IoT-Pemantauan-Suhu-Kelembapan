#include <WiFi.h>
#include <PubSubClient.h>

// --- 1. EDIT KONFIGURASI WIFI & MQTT DI SINI ---
const char* ssid = "NAMA_WIFI_KAMU";      // Ganti nama WiFi
const char* password = "PASSWORD_WIFI";   // Ganti password WiFi

// Kita pakai Broker Gratisan untuk tes (EMQX Public Broker)
const char* mqtt_server = "broker.emqx.io"; 
const int mqtt_port = 1883;

// Topik Unik (Biar gak tabrakan sama orang lain, ganti 'nama_kamu' bebas)
const char* topic_status = "proyek/air/status_fauzan"; 

// --- PIN SENSOR ---
const int pinSensor = 15;

WiFiClient espClient;
PubSubClient client(espClient);
unsigned long lastMsg = 0;

// Fungsi Koneksi WiFi
void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Menghubungkan ke ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Terhubung!");
}

// Fungsi Koneksi Ulang ke MQTT Broker jika putus
void reconnect() {
  while (!client.connected()) {
    Serial.print("Mencoba koneksi MQTT...");
    // Membuat ID Client random agar tidak ditolak broker
    String clientId = "ESP32Client-";
    clientId += String(random(0xffff), HEX);
    
    if (client.connect(clientId.c_str())) {
      Serial.println("Terhubung!");
    } else {
      Serial.print("Gagal, rc=");
      Serial.print(client.state());
      Serial.println(" coba lagi dalam 5 detik");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(pinSensor, INPUT_PULLUP); // Tetap INPUT_PULLUP sesuai sensor NPN kamu
  
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Kirim data setiap 2 detik sekali (biar gak spamming)
  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    
    int sensorState = digitalRead(pinSensor);
    String msg;

    // LOGIKA NPN: LOW = ADA AIR
    if (sensorState == LOW) {
      msg = "ADA AIR 🌊";
    } else {
      msg = "KERING ⛔";
    }

    Serial.print("Publish message: ");
    Serial.println(msg);
    
    // Kirim ke Broker
    client.publish(topic_status, msg.c_str());
  }
}
