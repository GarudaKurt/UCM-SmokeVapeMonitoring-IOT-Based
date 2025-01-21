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
  readSensor();
  calibrateMQ2(); //take note calibrate this sensor during the actual testing in the environment 
  calibrateMQ135();
  delay(1000);
}

