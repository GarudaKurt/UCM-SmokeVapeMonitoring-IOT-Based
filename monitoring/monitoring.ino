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
int calculatedThreshold_MQ2 = 0;
int calculatedThreshold_MQ135 = 0;
int smokeSamples[sampleSize];
int smokeSamples1[sampleSize];
int sampleCount = 0;

int calculateAverageSmoke_MQ2() {
    int sum = 0;
    for (int i = 0; i < averagingSize; i++) {
        sum += smokeSamples[i];
    }
    return sum / averagingSize;
}

int calculateAverageSmoke_MQ135() {
    int sum = 0;
    for (int i = 0; i < averagingSize; i++) {
        sum += smokeSamples1[i];
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

    if (sampleCount < sampleSize) {
        smokeSamples[sampleCount] = smokePPM;
        smokeSamples1[sampleCount] = smokePPM1;
        sampleCount++;
    }

    if (sampleCount >= sampleSize) {
        for (int i = 0; i < averagingSize - 1; i++) {
            smokeSamples[i] = smokeSamples[i + 1];
            smokeSamples1[i] = smokeSamples1[i + 1];
        }
        smokeSamples[averagingSize - 1] = smokePPM;
        smokeSamples1[averagingSize - 1] = smokePPM1;

        int avgMQ2 = calculateAverageSmoke_MQ2();
        int avgMQ135 = calculateAverageSmoke_MQ135();
        calculatedThreshold_MQ2 = avgMQ2+ 100;
        calculatedThreshold_MQ135 = avgMQ135+ 100;

        Serial.print("Average Smoke MQ2: ");
        Serial.println(avgMQ2);
        Serial.print("Average Smoke MQ135: ");
        Serial.println(avgMQ135);
        Serial.print("Calculated Threshold: ");
        Serial.println(calculatedThreshold);
    }

    Serial.print("Threshold: ");
    Serial.println(calculatedThreshold);

    if (calculatedThreshold_MQ2 != 0 && smokePPM >= calculatedThreshold_MQ2) {
        Serial.print("MQ2 Value PPM: ");
        Serial.println(smokePPM);
        alarmDisplay();
        buzzerStart();
        isAlarmActivate = true;
    } else if (calculatedThreshold_MQ135 != 0 && smokePPM1 >= calculatedThreshold_MQ135) {
        Serial.print("MQ135 Value PPM: ");
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
