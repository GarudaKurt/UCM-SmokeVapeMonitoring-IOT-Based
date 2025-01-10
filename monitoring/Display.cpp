#include "Display.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void initLCD() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing.... ");
}

void wifiDisplayError() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Failed!");
}
void updateDisplay(int mq2, int mq135) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sensor 1: ");
  lcd.setCursor(10, 0);
  lcd.print(mq2);

  lcd.setCursor(0, 1);
  lcd.print("Sensor 2: ");
  lcd.setCursor(10, 1);
  lcd.print(mq135);
}
void alarmDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smoke Detected");
  lcd.setCursor(0,1);
  lcd.print("Action required!");
}
