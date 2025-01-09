#include <Wire.h>

#define mq2 A0
#define mq135 A1

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int16_t mq2Val = analogRead(mq2);
  int16_t mq135Val = analogRead(mq135);

  int mq2Value = (mq2Val / 4.095);
  int mq135Value = (mq135Val / 4.095);
  Serial.print("MQ2 Value: ");
  Serial.println(mq2Val);
  Serial.print("MQ135 Value: ");
  Serial.println(mq135Value);

  delay(1000);
}

