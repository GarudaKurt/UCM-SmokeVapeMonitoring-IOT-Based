#include "Display.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void initLCD() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Initializing.... ");
  delay(1000);
  lcd.clear();
}

void clearDisplay() {
  lcd.clear();
}
void wifiDisplayError() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WiFi Failed!");
}
void updateDisplay(int smoke, const char *time, const char *date) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Clean Air: ");
  lcd.print(smoke);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("LOG:");
  lcd.setCursor(5,1);
  lcd.print(time);
  lcd.setCursor(11,1);
  lcd.print(date);
}
void alarmDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Smoke Detected");
  lcd.setCursor(0,1);
  lcd.print("Action required!");
}

void displayClear() {
  lcd.clear();
}
