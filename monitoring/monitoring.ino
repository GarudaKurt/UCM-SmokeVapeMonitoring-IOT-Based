#include <Arduino.h>
#include <Wire.h>

#include "alert.h"
#include "configFirebase.h"
#include "Display.h"

const float minThreshold = 100.00; //change the value base on the average baseline results of calibratingMQ2() sensors
const float maxThreshold = 500.00; //change the value base on the average baseline results of calibratingMQ135() sensors
const int buzzerPin = 11;

float mq2Val = 0;
float mq135Val = 0;

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
