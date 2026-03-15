#include "sensors.h"

// FR sensor depenedencies
#include <Arduino.h>
#include <Wire.h> // Arduino library for I2C

// Pressure sensor dependencies
#include <HX711.h>




// ---------- Pressure Sensor Code ------------

HX711 psens; // define HX711 object
uint8_t DT_PIN = 5; // HX711 data pin
uint8_t SCK_PIN = 6; // HX711 clock pin
float SCALE = 42.255; // scale factor for converting raw sensor data to pressure units (calibrated experimentally)
long OFFSET = 41500; // offset for guage pressure (calibrated experimentally)


bool setupPressureSensor() {
  psens.begin(DT_PIN, SCK_PIN);
  psens.set_scale(SCALE);
  psens.set_offset(OFFSET);
  return true;
}


bool updatePressure() {
  system_state.P = (float)psens.get_units(1);
  return true;
}




// ---------- Flow Rate Sensor Code ------------

const int ADDRESS = 0x40; // Standard address for Liquid Flow Sensors

bool setupFlowRateSensor() {
  int ret;

  Wire.begin();       // join i2c bus (address optional for master)

  do {
    // Soft reset the sensor
    Wire.beginTransmission(ADDRESS);
    Wire.write(0xFE);
    ret = Wire.endTransmission();

  } while (ret != 0);

  delay(50); // wait long enough for chip reset to complete
  return true;
}


bool updateFlowRate() {

  int ret;
  uint16_t raw_sensor_value;

  // To perform a measurement, first send 0xF1 to switch to measurement mode,
  // then read 2 bytes + 1 CRC byte from the sensor.
  Wire.beginTransmission(ADDRESS);
  Wire.write(0xF1);
  ret = Wire.endTransmission();
  if (ret != 0) {
    // Error during write measurement mode command
    return false;

  } else {
    Wire.requestFrom(ADDRESS, 2);       // reading 2 bytes ignores the CRC byte
    if (Wire.available() < 2) {
      // Error while reading flow measurement
      return false;
    } else {
      raw_sensor_value  = Wire.read() << 8; // read the MSB from the sensor
      raw_sensor_value |= Wire.read();      // read the LSB from the sensor

      system_state.Q = (float) raw_sensor_value;
      return true;
    }
  
  }
}