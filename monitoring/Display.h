#ifndef __DISPLAY__H
#define __DISPLAY__H

void initLCD();
void wifiDisplayError();
void alarmDisplay();
void updateDisplay(int mq2, int mq135, const char *time, const char *date);
//void historyDisplay(const char * time, const char * date);
void clearDisplay();

#endif