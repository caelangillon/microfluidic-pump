#ifndef FLOW_RATE_SENSOR_H
#define FLOW_RATE_SENSOR_H

#include <Arduino.h>
#include "sharedData.h"

// Function declarations for flow rate sensor operations
bool setupFlowRateSensor();
bool updateFlowRate();

#endif // FLOW_RATE_SENSOR_H