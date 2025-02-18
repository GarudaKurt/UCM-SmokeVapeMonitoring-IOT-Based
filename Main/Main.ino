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
  Serial.print("MQ2 Value: ");
  Serial.println(readMQ2Value());
  Serial.print("MQ135 Value: ");
  Serial.println(readMQ135Value());
  readSensor();
  delay(1000);
}

