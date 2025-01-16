#include <Wire.h>
#include <Arduino.h>
#include "configFirebase.h"
#include "Sensors.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  initSensors();
  initFirebase();
}

void loop() {
  // put your main code here, to run repeatedly:
  readSensor(); //disregards this function once you will get the actuail baseline of the 2 sensors
  // Calibrate the MQ2 sensor to get the baseline reading for smoke detection.
  // Note: Test this in the actual environment where the device will be implemented 
  // to get an accurate baseline reading.
  float baseline = calibrateMQ2(); 
  Serial.print("MQ2 Baseline Result: ");
  Serial.println(baseline); // Print the baseline of MQ2 Smoke reading
  float baseline1 = calibrateMQ135();
  Serial.print("MQ135 Baseline Resut: ");
  Serial.println(baseline1); // Print the baseline of MQ135 Smoke reading
  delay(1000);
}

