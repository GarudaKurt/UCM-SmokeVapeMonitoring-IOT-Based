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
int mq2Val = 0;
int smokePPM = 0;

const int sampleSize = 20;  // We need 20 samples value to calculate avera
int calculatedThreshold = 0;  // By default we set 0 the threshold, but once we get the average results we will just added +300 value for the smoke present.

int calculateAverage() {
    int sum = 0;
    for (int i = 0; i < sampleSize; i++) {
        smokeReadings[i] = readSmoke();
        sum += smokeReadings[i];
        delay(100);
    }
    return sum / sampleSize;
}

void setup() {
  Serial.begin(115200);
  initLCD();
  initFirebase();

  int avgSmoke = calculateAverageSmoke();
  calculatedThreshold = avgSmoke + 300;  // for smoke present, we need to add +300 value based on the average readings.
  Serial.print("Calculated Average Smoke: ");
  Serial.println(avgSmoke);
  Serial.print("Adaptive Threshold: ");
  Serial.println(calculatedThreshold);
  delay(1000);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - prevMillis >= interval) {

    mq2Val = readMQ2Sensor();
    smokePPM = readSmoke();
    Serial.print("Threshold: ");
    Serial.println(calculatedThreshold);
    if(smokePPM >= calculatedThreshold) {
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
      Serial.println(smokePPM);
      if(isAlarmActivate){
        lastTime =  getTime();
        lastDate =  getDate();
        updateDisplay(smokePPM, mq2Val, getTime(), getDate());
        isAlarmActivate = false;
     }
      buzzerStop();
    }
    prevMillis = currentMillis;
  }
}
