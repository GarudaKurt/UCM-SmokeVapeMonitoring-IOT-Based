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
unsigned long interval = 1000;

void setup() {
  Serial.begin(115200);
  initLCD();
  initFirebase();
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
    } else {
      updateDisplay(mq2Val, mq135Val);
      Serial.print("MQ2 Value: ");
      Serial.println(mq2Val);
      Serial.print("MQ135 Value: ");
      Serial.println(mq135Val);
      buzzerStop();
    }
  }
}
