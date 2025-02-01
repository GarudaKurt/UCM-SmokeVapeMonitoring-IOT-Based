#ifndef __SENSORS__H
#define __SENSORS__H

void initSensors();
int32_t readMQ2Value();
int32_t readMQ135Value();
float calibrateMQ135();
float calibrateMQ2();

#endif
