#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <Arduino.h>
#include "sharedData.h"

float PID_V1(float V1_setpoint, float V1_measured);
float PID_V2(float V2_setpoint, float V2_measured);
float PID_FR(float FR_setpoint, float FR_measured);
void resetControllers();

#endif // CONTROLLER_H