#include "configFirebase.h"
#include "Display.h"
#include <time.h>
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

#define WIFI_SSID "vapemonitoring" //change this based on your mobile hotspot name and make sure to set 2.4Ghz your mobile hotspot
#define WIFI_PASSWORD "vapemonitoring123" //change this  based on youe hotspot password
#define API_KEY "AIzaSyCL1xEbJjKdtq3AzhygI7OuwaXqSDFHWlU"
#define DATABASE_URL "https://ucm-vape-monitoring-default-rtdb.firebaseio.com"
#define USER_EMAIL "vapemonitoring@gmail.com" //create OAuth user email
#define USER_PASSWORD "vapemonitoring" //create OAuth user password

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

int timeZone = 8 * 3600;  // Philippine Time
int dst = 0;

void initFirebase() {

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Not connected to WiFi, please check!");
    wifiDisplayError();
    delay(300);
  }

  configTime(timeZone, dst, "pool.ntp.org","time.nist.gov");
  Serial.println("Waiting for time....");
  while(!time(nullptr)){
    Serial.println("Time is nullptr!");
    delay(1000);
  }

  clearDisplay();
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

int readSmoke() {
  if (Firebase.ready()) {
    if (Firebase.getString(fbdo, "/monitoring/mq135")) {
      return fbdo.stringData().toInt();
    }
    return -1;
  }
}

const char* getTime() {
  static char buffer[10];
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  snprintf(buffer, sizeof(buffer), "%02d:%02d", p_tm->tm_hour, p_tm->tm_min);
  return buffer;
}

const char* getDate() {
  static char buffer[10];
  time_t now = time(nullptr);
  struct tm* p_tm = localtime(&now);
  snprintf(buffer, sizeof(buffer), "%02d/%02d", p_tm->tm_mday, p_tm->tm_mon + 1);
  return buffer;
}

