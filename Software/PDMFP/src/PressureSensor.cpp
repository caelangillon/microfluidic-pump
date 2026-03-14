#include "PressureSensor.h"
#include <HX711.h>


// pressure sensor definitions
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