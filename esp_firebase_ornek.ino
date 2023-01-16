#include <Arduino.h>
#if defined(ESP32)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"

#define WIFI_SSID "....." // wifi ağ adını " " içine yazınız.
#define WIFI_PASSWORD "....." // wifi şifresini " " içine yazınız.

#define API_KEY ".............." // firebase api keyi " " içine yazınız.
#define DATABASE_URL "............" //firebase url " " içine yazınız.

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

int x = 0;
float y = 0.0;
void setup() {

  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Ağa bağlanıyor");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Bağlandı. IP Adresi: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  Firebase.signUp(&config, &auth, "", "");
  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

}

void loop() {

  Firebase.RTDB.setInt(&fbdo, "int", x);
  Firebase.RTDB.setFloat(&fbdo, "float", y);
  x = x + 15;
  y = y + 0.7;
  delay(500);

  //Aşağıdaki satır firebasedeki deneme keyinden veri almak için kullanılır.

  String deneme = Firebase.RTDB.getString(&fbdo, "/deneme") ? String(fbdo.to<String>()).c_str() : fbdo.errorReason().c_str();

}
