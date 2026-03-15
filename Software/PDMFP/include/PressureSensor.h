#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

#include <Arduino.h>
#include "SharedData.h"

// Function declarations for pressure sensor operations
bool setupPressureSensor();
bool updatePressure();

#endif // PRESSURE_SENSOR_H can move to after include
