#include <Arduino.h>
#include <Wire.h>

#include "alert.h"
#include "configFirebase.h"
#include "Display.h"

unsigned long prevMillis = 0;
const int interval = 1000;

bool isAlarmActivate = false;
const char *lastTime = "";
const char *lastDate = "";
int smokePPM = 0;
int smokePPM1 = 0;

const int sampleSize = 20;
const int averagingSize = 15; 
int calculatedThreshold = 0;
int smokeSamples[sampleSize];
int sampleIndex = 0;
int sampleCount = 0;
bool samplesCollected = false;

// We need to calculate the average smoke PPM from the collected 15 samples then get the average
int calculateAverageSmoke() {
    int sum = 0;
    for (int i = 0; i < averagingSize; i++) {
        sum += smokeSamples[i];
    }
    return sum / averagingSize;
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

    smokePPM = readMQ2Sensor();
    smokePPM1 = readSmoke();

    // Collect all samples in the array
    if (sampleCount < sampleSize) {
        smokeSamples[sampleCount] = smokePPM;
        sampleCount++;
    }

    if (sampleCount >= sampleSize) {
        for (int i = 0; i < averagingSize - 1; i++) {
            smokeSamples[i] = smokeSamples[i + 1];
        }
        smokeSamples[averagingSize - 1] = smokePPM;

        int avgSmoke = calculateAverageSmoke();
        calculatedThreshold = avgSmoke + 100;  //We need to add on +100 for smoke are occuring in the area

        Serial.print("Calculated Average Smoke: ");
        Serial.println(avgSmoke);
        Serial.print("Adaptive Threshold: ");
        Serial.println(calculatedThreshold);
    }

    // Check if the threshold is exceeded
    Serial.print("Threshold: ");
    Serial.println(calculatedThreshold);

    if (calculatedThreshold != 0 && smokePPM >= calculatedThreshold) {
        Serial.print("MQ2 Value: ");
        Serial.println(smokePPM);
        Serial.print("Smoke PPM: ");
        Serial.println(smokePPM1);
        alarmDisplay();
        buzzerStart();
        isAlarmActivate = true;
    } else {
        updateDisplay(smokePPM1, smokePPM, lastTime, lastDate);
        Serial.print("MQ2 Value: ");
        Serial.println(smokePPM);
        Serial.print("MQ135 Value: ");
        Serial.println(smokePPM1);
        if (isAlarmActivate) {
            lastTime = getTime();
            lastDate = getDate();
            updateDisplay(smokePPM1, smokePPM, getTime(), getDate());
            isAlarmActivate = false;
        }
        buzzerStop();
    }

    prevMillis = currentMillis;
  }
}
