#include <Wire.h>
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
#define WIFI_PASSWORD "Tyler_properties#0124"
#define API_KEY "AIzaSyCL1xEbJjKdtq3AzhygI7OuwaXqSDFHWlU"
#define DATABASE_URL "https://ucm-vape-monitoring-default-rtdb.firebaseio.com"
#define USER_EMAIL "vapemonitoring@gmail.com" //create OAuth user email
#define USER_PASSWORD "vapemonitoring" //create OAuth user password

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;

#define mq2Pin 4
#define mq135Pin 5

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.println("Not connected to wifi please check!");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  
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

  Serial.println("Setup complete.");
  Serial.println("");
  delay(100);
}

void loop() {

  if (Firebase.ready() && (millis() - sendDataPrevMillis > 15000 || sendDataPrevMillis == 0)) { 
    sendDataPrevMillis = millis();
    
    int16_t mq2Value = analogRead(mq2Pin);
    int16_t mq135Value = analogRead(mq135Pin);

    int mq2ppmValue = (mq2Value / 4.095);
    int mq135ppmValue = (mq134Value / 4.095);

    Serial.println("MQ2 PPM: "+mq2ppmValue);
    Serial.println"MQ135 PPM: "+mq135ppmValue);

    bool mq2 = Firebase.setInt(fbdo, F("/monitoring/mq2",mq2ppmValue))
    bool mq135 = Firebase.setInt(fbdo, F("/monitoring/mq135",mq135ppmValue))

    if(!mq2 || !mq135)
      Serial.println("Failed send data");
    
  }
  Serial.println("");
  delay(500);
}