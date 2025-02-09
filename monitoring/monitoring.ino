#include <Arduino.h>
#include <Wire.h>

#include "alert.h"
#include "configFirebase.h"
#include "Display.h"

const int maxThreshold = 2900;
const int buzzerPin = 11;

unsigned long prevMillis = 0;
const int interval = 1000;

bool isAlarmActivate = false;
const char *lastTime = "";
const char *lastDate = "";
void setup() {
  Serial.begin(115200);
  initLCD();
  initFirebase();
  delay(1000);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - prevMillis >= interval) {
    prevMillis = currentMillis;

    int mq2Val = readMQ2Sensor();
    int smokePPM = readSmoke();

    if(smokePPM >= maxThreshold) {
      Serial.print("MQ2 Value: ");
      Serial.println(mq2Val);
      Serial.print("Smoke PPM: ");
      Serial.println(smokePPM);
      alarmDisplay();
      buzzerStart();
      isAlarmActivate = true;
    } else {
      updateDisplay(smokePPM, mq2Val, lastTime, lastDate);
      Serial.print("MQ2 Value: ");
      Serial.println(mq2Val);
      Serial.print("MQ135 Value: ");
      Serial.println(mq135Val);
      if(isAlarmActivate){
        lastTime =  getTime().c_str();
        lastDate =  getDate().c_str()
        updateDisplay(smokePPM, getTime().c_str(), getDate().c_str());
        isAlarmActivate = false;
     }
      buzzerStop();
    }
  }
}
