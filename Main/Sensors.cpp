#include "Sensors.h"
#include <Arduino.h>
#include <MQ2.h>
#include <MQ135.h>
#include <DHT11.h>

const int PIN_MQ2 = 33;
const int PIN_MQ135 = 32;
const int DHT_PIN = 34;

DHT11 dht11(DHT_PIN);

MQ135 mq135_sensor(PIN_MQ135);
MQ2 mq2(PIN_MQ2);

float smokeMQ2, smokeMQ135 = 0;
int temperature = 0;
int humidity = 0;

void initSensors() {
  mq2.begin();
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db); // 0-3.3V range
}

float readMQ2Value() {
  //smokeMQ2 = mq2.readSmoke();
  smokeMQ2 = analogRead(PIN_MQ2);
  return smokeMQ2 / 4.095;
}
float calibrateMQ2() {
  return mq2.readSmoke();
}

float calibrateMQ135() {
  return mq135_sensor.getCorrectedPPM(temperature, humidity);;
}

float readMQ135Value() {
  smokeMQ135 = analogRead(PIN_MQ135);
  return smokeMQ135 / 4.095;
}



