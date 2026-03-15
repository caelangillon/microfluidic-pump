#include "targetGenerator.h"
#include <Arduino.h>

float start_time = 0.0;
float target = 0.0;

void resetTargets() {   // resets timer for stepped/sinusoidal control
  start_time = millis() / 1000.0;
}

void updateTarget() {   // updates flowrate or pressure target based on control selection, type and parameters (e.g. stepped, sinusoidal, etc.)

    // __ Type 1 - Constant __
    // param_1 = constant value

    // __ Type 2 - Stepped __
    // param_1 = starting value
    // param_2 = step size
    // param_3 = time between steps

    // __ Type 3 - Sinusoidal __
    // param_1 = frequency
    // param_2 = amplitude
    // param_3 = offset

    // __ Type 4 - Pulsed __
    // param_1 = frequency
    // param_2 = duty cycle
    // param_3 = amplitude

    // Constant target
    if (ctrl_params.type == 1) {
      target = ctrl_params.param_1;
    }

    // Stepped target
    else if (ctrl_params.type == 2) {
      int num_steps = floor((system_state.clock - start_time) / ctrl_params.param_3);
      target = ctrl_params.param_1 + num_steps * ctrl_params.param_2;
    }

    // Sinusoidal target
    else if (ctrl_params.type == 3) {
      target = ctrl_params.param_2 * sin(2 * PI * ctrl_params.param_1 * (system_state.clock - start_time)) + ctrl_params.param_3;
    }

    // Pulsed target
    else if (ctrl_params.type == 4) {
      float period = 1.0 / ctrl_params.param_1;
      float time_in_period = fmod(system_state.clock - start_time, period);
      if (time_in_period < ctrl_params.param_2 * period) {
        target = ctrl_params.param_3;
      } else {
        target = 0;
      }
    }

    // Update target in system state
    if (ctrl_params.selection == 1) {
      system_state.P_target = target;
    }
    else if (ctrl_params.selection == 2) {
      system_state.Q_target = target;
    }
    
}

