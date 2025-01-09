#include "configFirebase.h"
#include "Display.h"
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

#define WIFI_SSID "teloy"
#define WIFI_PASSWORD "Tyler_property#0124"
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
    wifiDisplayError();
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

int readMQ2Sensor() {
  if (Firebase.ready()) {
    if (Firebase.getString(fbdo, "/monitoring/mq2")) {
      return fbdo.stringData().toInt();
    }
    return -1;
  }
}

int readMQ135Sensor() {
  if (Firebase.ready()) {
    if (Firebase.getString(fbdo, "/monitoring/mq135")) {
      return fbdo.stringData().toInt();
    }
    return -1;
  }
}

