#include "HX711.h"

const int DT_PIN = 7;
const int CLK_PIN = 8;

float known_pressure = 101325; // (Pa, remember this is GUAGE pressure)
float CF; // Calibration factor
int no = 10; // Number of ADC readings per poll

HX711 psens;

void setup() {
  while (!Serial) {
    delay(250);
  }

  Serial.begin(9600);
  psens.begin(DT_PIN, CLK_PIN);

  while (!psens.is_ready()) {
    Serial.println("HX711 not found.");
    delay(250);
  }

  // Zero the sensor
  psens.set_scale(1); // Set CF = 1
  Serial.println("Release all pressure on the sensor. 2 second delay. ('tare' measures and sets the offset)");
  delay(2000);
  psens.tare();
  Serial.println("Tare complete.");
  
  // Measure CF
  Serial.print("Apply a known pressure. 5 second delay.");
  delay(5000);
  long reading = psens.get_units(10); // Averages 10 measurements
  Serial.print("Result: ");
  Serial.println(reading);

  CF = reading / known_pressure ; 
  psens.set_scale(CF);
  Serial.print("Calibration factor: ");
  Serial.println(CF);
}

void loop() {
  // Acquire pressure sensor measurements
  float pressure_measurement = psens.get_units(no)/1000;

  // Print measurement & info
  Serial.print("Calibration factor: ");
  Serial.print(CF);
  Serial.print(" | ");
  Serial.print("Measurement: ");
  Serial.print(pressure_measurement);
  Serial.print(" kPa");
  Serial.print(" | ");
  Serial.print("ADC readings per poll: ");
  Serial.println(no);
  
  delay(1000);
}