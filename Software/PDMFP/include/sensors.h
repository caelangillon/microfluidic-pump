#ifndef SENSORS_H
#define SENSORS_H

#include <Arduino.h>
#include "sharedData.h"

// Function declarations for sensor operations
bool setupFlowRateSensor();
bool updateFlowRate();

bool setupPressureSensor();
bool updatePressure();

#endif // SENSORS_H