#include <MQ135.h>

/*  MQ135 gas sensor
    Datasheet can be found here: https://www.olimex.com/Products/Components/Sensors/SNS-MQ135/resources/SNS-MQ135.pdf

    Application
    They are used in air quality control equipments for buildings/offices, are suitable for detecting of NH3, NOx, alcohol, Benzene, smoke, CO2, etc

    Original creator of this library: https://github.com/GeorgK/MQ135
*/

#define PIN_MQ135 A0
#define PIN_MQ135_1 A1

MQ135 mq135_sensor(PIN_MQ135);
// MQ135 mq135_sensor_1(PIN_MQ135_1);

float temperature = 21.0; // Assume current temperature. Recommended to measure with DHT22
float humidity = 25.0; // Assume current humidity. Recommended to measure with DHT22

void setup() {
  Serial.begin(9600);
}

void loop() {
  float rzero = mq135_sensor.getRZero();
  float correctedRZero = mq135_sensor.getCorrectedRZero(temperature, humidity);
  float resistance = mq135_sensor.getResistance();
  float ppm = mq135_sensor.getPPM();
  float correctedPPM = mq135_sensor.getCorrectedPPM(temperature, humidity);

  // float rzero_1 = mq135_sensor_1.getRZero();
  // float correctedRZero_1 = mq135_sensor_1.getCorrectedRZero(temperature, humidity);
  // float resistance_1 = mq135_sensor_1.getResistance();
  // float ppm_1 = mq135_sensor_1.getPPM();
  // float correctedPPM_1 = mq135_sensor_1.getCorrectedPPM(temperature, humidity);

  Serial.print("MQ135 RZero: ");
  Serial.print(rzero);
  Serial.print("\t Corrected RZero: ");
  Serial.print(correctedRZero);
  Serial.print("\t Resistance: ");
  Serial.print(resistance);
  Serial.print("\t PPM: ");
  Serial.print(ppm);
  Serial.print("\t Corrected PPM: ");
  Serial.print(correctedPPM);
  Serial.println("ppm");

  // Serial.print("MQ135 RZero_1: ");
  // Serial.print(rzero_1);
  // Serial.print("\t Corrected RZero_1: ");
  // Serial.print(correctedRZero_1);
  // Serial.print("\t Resistance_1: ");
  // Serial.print(resistance_1);
  // Serial.print("\t PPM_1: ");
  // Serial.print(ppm_1);
  // Serial.print("\t Corrected PPM_1: ");
  // Serial.print(correctedPPM_1);
  // Serial.println("ppm_1");

  delay(300);
}
