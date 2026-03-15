#ifndef CONTROLLERS_H
#define CONTROLLERS_H

#include <Arduino.h>
#include "sharedData.h"

void controlFlowRate();    // calculates target pressure and updates system_state.P_target
void controlPressure();    // calculates valve DCs updates system_state.DC1 and system_state.DC2

#endif // CONTROLLERS_H