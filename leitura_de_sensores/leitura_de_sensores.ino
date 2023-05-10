#include <Wire.h>
//#include <SPI.h>
#include <SoftwareSerial.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_TSL2561_U.h>
#include <Adafruit_BME280.h>

//BME280
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)

//Sensor TGS 2602
#define VALOR A0


//Sensor TGS 2602
float analogValue = 0.0;
float gain = 1.08;
//BME280
unsigned long delayTime;



Adafruit_BME280 bme;
SoftwareSerial espSerial(4, 11);
Adafruit_TSL2561_Unified tsl = Adafruit_TSL2561_Unified(TSL2561_ADDR_FLOAT, 12345);


void setup() {
  espSerial.begin(115200);
  Serial.begin(115200);
  Serial.println("Inicio da leitura dos sensores");
  Serial.println("===Smart-Lab===");
  unsigned status;
  status = bme.begin(0x77);
  if (!status) {
          Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
          Serial.print("SensorID was: 0x"); Serial.println(bme.sensorID(),16);
          Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
          Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
          Serial.print("        ID of 0x60 represents a BME 280.\n");
          Serial.print("        ID of 0x61 represents a BME 680.\n");
          while (1) delay(10);
      }
}

void loop() {
  printValoresBME();
  sensorLuz();
  voc();
  Serial.println("==============================================================");

  delay(60000);
}
