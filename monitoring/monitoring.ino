#include <Arduino.h>
#include <Wire.h>

#include "alert.h"
#include "configFirebase.h"
#include "Display.h"

const int minThreshold = 100;
const int maxThreshold = 500;
const int buzzerPin = 11;

int mq2Val = 0;
int mq135Val = 0;

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

    mq2Val = readMQ2Sensor();
    mq135Val = readMQ135Sensor();

    if(mq2Val >= minThreshold && mq135Val <= maxThreshold) {
      Serial.print("MQ2 Value: ");
      Serial.println(mq2Val);
      Serial.print("MQ135 Value: ");
      Serial.println(mq135Val);
      alarmDisplay();
      buzzerStart();
      isAlarmActivate = true;
    } else {
      updateDisplay(mq2Val, mq135Val, lastTime, lastDate);
      Serial.print("MQ2 Value: ");
      Serial.println(mq2Val);
      Serial.print("MQ135 Value: ");
      Serial.println(mq135Val);
      if(isAlarmActivate){
        lastTime =  getTime().c_str();
        lastDate =  getDate().c_str()
        updateDisplay(mq2Val, mq135Val, getTime().c_str(), getDate().c_str());
        isAlarmActivate = false;
     }
      buzzerStop();
    }
  }
}
