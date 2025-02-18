#include "Sensors.h"
#include <Arduino.h>
#include <MQ2.h>
#include <MQ135.h>
#include <Wire.h>

#define PIN_MQ2 34
#define PIN_MQ135  32

//DHT11 dht11(DHT_PIN);

MQ135 mq135_sensor(PIN_MQ135);
MQ2 mq2(PIN_MQ2);

int temperature = 0;
int humidity = 0;

void initSensors() {
  //Wire.begin(23, 22);
  //dht.begin();
  analogSetAttenuation(ADC_11db);
  pinMode(PIN_MQ135, INPUT);
  pinMode(PIN_MQ132, INPUT);
  
}
float calibrateMQ2() {
  return mq2.readSmoke();
}

float calibrateMQ135() {
 // return mq135_sensor.getCorrectedPPM(temperature, humidity);;
}

int readMQ2Value() {
  int smokeMQ2ppm = analogRead(PIN_MQ2);
  return smokeMQ2ppm;
}

int readMQ135Value() {
  int smokeMQ135ppm = analogRead(PIN_MQ135);
  return smokeMQ135ppm;
}



