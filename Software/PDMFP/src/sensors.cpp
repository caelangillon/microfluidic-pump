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

  unsigned int sensor_resolution = 13;

  int ret;
  uint16_t adv_user_reg_original;
  uint16_t adv_user_reg_new;
  uint16_t resolution_mask;

  Wire.begin();       // join i2c bus (address optional for master)
  Wire.setClock(100000); // set I2C clock speed to 100000 for 80hz

  do {
    // Soft reset the sensor
    Wire.beginTransmission(ADDRESS);
    Wire.write(0xFE);
    ret = Wire.endTransmission();

  } while (ret != 0);

  delay(50); // wait long enough for chip reset to complete

  
  // Set resolution to 13bits
  resolution_mask = 0xF1FF | ((sensor_resolution - 9) << 9);


  // Change mode to read adv. user register
  Wire.beginTransmission(ADDRESS);
  Wire.write(0xE5);
  ret = Wire.endTransmission();

  if (ret != 0) {
    return false;
  } 
  
  else {
    // Read the content of the adv user register
    Wire.requestFrom(ADDRESS, 2);
    if (Wire.available() < 2) {
      return false;

    } else {
      adv_user_reg_original  = Wire.read() << 8;
      adv_user_reg_original |= Wire.read();
      adv_user_reg_new = (adv_user_reg_original | 0x0E00) & resolution_mask;

      // Apply resolution changes:
      // Change mode to write to adv. user register
      Wire.beginTransmission(ADDRESS);
      Wire.write(0xE4);                           // Send command
      Wire.write((byte)(adv_user_reg_new >> 8));      // Send MSB
      Wire.write((byte)(adv_user_reg_new & 0xFF));    // Send LSB
      ret = Wire.endTransmission();
      if (ret != 0) {
        return false;
      }
    }
  }

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