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

const int sampleSize = 20;
int calculatedThreshold = 0;  
int smokeSamples[sampleSize];
int sampleIndex = 0;
bool samplesCollected = false;

//calculate the average smoke PPM from collected samples
int calculateAverageSmoke() {
    int sum = 0;
    for (int i = 0; i < sampleSize; i++) {
        sum += smokeSamples[i];
    }
    return sum / sampleSize;
}

void setup() {
  Serial.begin(115200);
  initLCD();
  initFirebase();
  delay(1000);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - prevMillis >= interval) {

    mq2Val = readMQ2Sensor();
    smokePPM = readSmoke();

    smokeSamples[sampleIndex] = smokePPM;
    sampleIndex++;

    // If we have collected 20 samples, compute the threshold
    if (sampleIndex >= sampleSize) {
      sampleIndex = 0;
      samplesCollected = true;
    }

    if (samplesCollected) {
      int avgSmoke = calculateAverageSmoke();
      calculatedThreshold = avgSmoke + 300;  // Adaptive threshold
      
      Serial.print("Calculated Average Smoke: ");
      Serial.println(avgSmoke);
      Serial.print("Adaptive Threshold: ");
      Serial.println(calculatedThreshold);
    }

    Serial.print("Threshold: ");
    Serial.println(calculatedThreshold);

    if(samplesCollected && calculatedThreshold != 0 && smokePPM >= calculatedThreshold) {
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
