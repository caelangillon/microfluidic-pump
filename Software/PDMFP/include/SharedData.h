#ifndef SHARED_DATA_H
#define SHARED_DATA_H

#include <Arduino.h>

struct controlParams {
  uint8_t selection = 0;    // 0: off  1: pressure control  2: flow rate control
  uint8_t type = 0;         // 0: off  1: constant  2: stepped  3: sinusoidal  4: Pulsed

  // __ Type 1 __
  // param_1 = constant value

  // __ Type 2 __
  // param_1 = starting value
  // param_2 = step size
  // param_3 = time between steps

  // __ Type 3 __
  // param_1 = frequency
  // param_2 = amplitude
  // param_3 = offset

  // __ Type 4 __
  // param_1 = frequency
  // param_2 = duty cycle
  // param_3 = amplitude

  float param_1 = 0;
  float param_2 = 0;
  float param_3 = 0;

};

struct pidGains {
  // Flow rate PID gains
  float P_FR = 0;
  float I_FR = 0;
  float D_FR = 0;
  // Valve 1 PID gains
  float P_V1 = 0.0006;
  float I_V1 = 0.0001;
  float D_V1 = 0;
  // Valve 2 PID gains
  float P_V2 = 0.019;
  float I_V2 = 0.05;
  float D_V2 = 0;
};

struct systemState {
  float clock = 0;      // time in seconds since system start
  float Q = 0;          // flow rate
  float Q_target = 0;   // flow rate target
  float P = 0;          // pressure
  float P_target = 0;   // pressure target
  float DC1 = 0;        // valve 1 duty cycle
  float DC2 = 0;        // valve 2 duty cycle
  float Vol = 7;        // volume fluid left in reservoir in mL, initialized to 7mL for testing purposes
};

struct controllerState {
  float prevFlowErr = 0;  // previous flow rate error
  float prevPressErr = 0; // previous pressure error
  float prevTime = 0;     // previous time
  float int_FR = 0;       // integral of flow rate error
  float int_Press = 0;    // integral of pressure error 
};

extern controlParams ctrl_params;
extern pidGains pid_gains;
extern systemState system_state;
extern controllerState controller_state;

#endif // SHARED_DATA_H