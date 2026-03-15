#include "FlowRateSensor.h"
#include <Arduino.h>
#include <Wire.h> // Arduino library for I2C

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