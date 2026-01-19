#include "HX711.h"

const int DT_PIN = 7;
const int CLK_PIN = 8;

float known_pressure = 100000;

float CF; // Calibration factor
int no = 10; // Number of ADC readings per poll

bool flag1 = true;

HX711 psens;

void setup() {

  // Arduino setup
  pinMode(11, OUTPUT);
  Serial.begin(115200);
  psens.begin(DT_PIN, CLK_PIN);

  while (!Serial) {
    delay(250);
  }

  while (!psens.is_ready()) {
    Serial.println("HX711 not found.");
    delay(250);
  }

  // Serial info
  Serial.println("---");
  Serial.println("The pressure sensor will now calibrate. The sensor will: ");
  Serial.println("1. Tare");
  Serial.println("2. Measure a known pressure");
  Serial.println("3. Acquire raw reading");
  Serial.println("4. Calculate and set the calibration factor (CF)");
  Serial.println("---");

  // Zero the sensor
  psens.set_scale(1); // CF = 1
  Serial.println("Release all pressure on the sensor. 3 second delay.");
  delay(3000);
  psens.tare(); // Measures and sets the offset
  Serial.println("Tare complete.");
  
  // Measure CF
  Serial.println("Apply a known pressure. Waiting...");
  while (flag1) {
    delay(100);

    if (Serial.available() > 0) {
      char cmd = Serial.read();
      if (cmd == 'w') {
        flag1 = false;
      }
    }
  }

  long reading = psens.get_units(10);
  Serial.print("Raw reading: ");
  Serial.println(reading);

  Serial.println("Pressure read succesful. Calibrating...");
  delay(100);

  CF = reading / known_pressure ; 
  psens.set_scale(CF);
  Serial.println("Calibration factor: ");
  Serial.print(CF);
}

void loop() {
  // Acquire pressure sensor measurements
  float pressure_measurement = psens.get_units(1);
  // Print measurement & info
  Serial.println(pressure_measurement);
}