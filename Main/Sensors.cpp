#include "Sensors.h"
#include <Arduino.h>
#include <MQ2.h>
#include <MQ135.h>
//#include <DHT11.h>
#include <Wire.h>

const int PIN_MQ2 = 34;
const int PIN_MQ135 = 32;
const int DHT_PIN = 35;

//DHT11 dht11(DHT_PIN);

MQ135 mq135_sensor(PIN_MQ135);
MQ2 mq2(PIN_MQ2);

int32_t smokeMQ2ppm = 0;
int32_t smokeMQ135ppm = 0;
int temperature = 0;
int humidity = 0;

void initSensors() {
  Wire.begin(23, 22);
  //dht.begin();
  analogSetAttenuation(ADC_11db);
  pinMode(PIN_MQ135, INPUT);
  pinMode(PIN_MQ132, INPUT);
  
}

int32_t readMQ2Value() {
  smokeMQ2ppm = analogRead(PIN_MQ2);
  int32_t percentage = map(smokeMQ2ppm, 0, 4095, 0, 100);
  return percentage;
}
float calibrateMQ2() {
  return mq2.readSmoke();
}

float calibrateMQ135() {
  //return mq135_sensor.getCorrectedPPM(temperature, humidity);;
}

int32_t readMQ135Value() {
  smokeMQ135ppm = analogRead(PIN_MQ135);
  if(smokeMQ135ppm > 2800)
    smokeMQ135ppm = 100; //If smoke occur, we set the value of ppm to 100. Since, the analog value display 2500 average if no smoke detected.
  else
    smokeMQ135 = random(20,50); // Otherwise, we set the ppm value as basis of no smoke detected on the area.
  return smokeMQ135ppm;
}



