#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <Arduino.h>

struct ControlParams {
  uint8_t selection = 0;
  uint8_t type = 0;
  float param_1 = 0;
  float param_2 = 0;
  float param_3 = 0;
};

struct PidGains {
  float P_FR = 0;
  float I_FR = 0;
  float D_FR = 0;
  float P_V1 = 0;
  float I_V1 = 0;
  float D_V1 = 0;
  float P_V2 = 0;
  float I_V2 = 0;
  float D_V2 = 0;
};

struct SystemState {
  float clock = 0;
  float Q = 0;
  float Q_target = 0;
  float P = 0;
  float P_target = 0;
  float DC1 = 0;
  float DC2 = 0;
  float Vol = 7;
};

extern ControlParams ctrl_params;
extern PidGains pid_gains;
extern SystemState system_state;

#endif // SHARED_DATA_H