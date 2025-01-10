#include <MQ2.h>
#include <MQ135.h>
#include <DHT11.h>


//change this with the pin that you use
#define pin A1
#define PIN_MQ135 A0 // MQ135 Analog Input Pin
#define DHTPIN 2 // DHT Digital Input Pin
DHT11 dht11(DHTPIN);

float lpg, co, smoke, calibrate;

MQ135 mq135_sensor(PIN_MQ135);

int temperature, humidity = 25; 

MQ2 mq2(pin);

void setup(){
  Serial.begin(9600);
  
  // calibrate the device
  mq2.begin();
}

void loop(){
  
  /*
   * read the values from the sensor, it returns
   * an array which contains 3 values.
   * 0 : LPG in ppm
   * 1 : CO in ppm
   * 2 : SMOKE in ppm
   */
  float* values= mq2.read(true); //set it false if you don't want to print the values to the Serial
  
  // lpg = values[0];
  lpg = mq2.readLPG();
  // co = values[1];
  co = mq2.readCO();
  // smoke = values[2];
  smoke = mq2.readSmoke();

  int result = dht11.readTemperatureHumidity(temperature, humidity);

  if(result != 0)
    Serial.println("Error reading DH11 temp and humd")

  // Check if any reads failed and exit early (to try again).
    if (isnan(humidity) || isnan(temperature)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }

  float rzero = mq135_sensor.getRZero();
  float correctedRZero = mq135_sensor.getCorrectedRZero(temperature, humidity);
  float resistance = mq135_sensor.getResistance();
  float ppm = mq135_sensor.getPPM();
  float correctedPPM = mq135_sensor.getCorrectedPPM(temperature, humidity);

  Serial.print("MQ135 RZero: ");
  Serial.print(rzero);
  Serial.print("\t Corrected RZero: ");
  Serial.print(correctedRZero);
  Serial.print("\t Resistance: ");
  Serial.print(resistance);
  Serial.print("\t PPM: ");
  Serial.print(ppm);
  Serial.print("ppm");
  Serial.print("\t Corrected PPM: ");
  Serial.print(correctedPPM);
  Serial.println("ppm");
  
  delay(1000);
}

