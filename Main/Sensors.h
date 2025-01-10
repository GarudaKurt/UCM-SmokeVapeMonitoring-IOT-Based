#ifndef __SENSORS__H
#define __SENSORS__H

void initSensors();
float readMQ2Value();
float readMQ135Value();
float calibrateMQ135();
float calibrateMQ2();

#endif