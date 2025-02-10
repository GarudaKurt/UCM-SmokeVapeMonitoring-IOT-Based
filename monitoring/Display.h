#ifndef __DISPLAY__H
#define __DISPLAY__H

void initLCD();
void wifiDisplayError();
void alarmDisplay();
void updateDisplay(int mq135ppm, int mq2ppm, const char *time, const char *date);
void clearDisplay();

#endif
