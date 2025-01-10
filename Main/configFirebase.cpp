#include "configFirebase.h"
#include "Sensors.h"
#include <Arduino.h>

#ifdef ESP32
#include <WiFi.h>
#include <FirebaseESP32.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <WiFiUdp.h>
#endif

#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>

#define WIFI_SSID "vapemonitoring"
#define WIFI_PASSWORD "vapemonitoring"
#define API_KEY "AIzaSyCL1xEbJjKdtq3AzhygI7OuwaXqSDFHWlU"
#define DATABASE_URL "https://ucm-vape-monitoring-default-rtdb.firebaseio.com"
#define USER_EMAIL "vapemonitoring@gmail.com" //create OAuth user email
#define USER_PASSWORD "vapemonitoring" //create OAuth user password

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void initFirebase() {

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Not connected to WiFi, please check!");
    delay(300);
  }

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.database_url = DATABASE_URL;
  config.token_status_callback = tokenStatusCallback;
  Firebase.reconnectWiFi(true);
  fbdo.setBSSLBufferSize(4096, 1024);
  Firebase.begin(&config, &auth);
  Firebase.setDoubleDigits(5);
}

void readSensor() {
  if (Firebase.ready()) {
    bool success = Firebase.setFloat(fbdo, "/monitoring/mq2", readMQ2Value());
    bool compile = Firebase.setFloat(fbdo, "/monitoring/mq135", readMQ135Value());
    Serial.print("MQ2 Val: ");
    Serial.println(readMQ2Value());
    Serial.print("MQ135 Val: ");
    Serial.println(readMQ135Value());
    if(!success || !compile)
      Serial.println("Failed to send to firebase");
  }
}

