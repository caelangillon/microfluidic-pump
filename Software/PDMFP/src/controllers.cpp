#include "controllers.h"

float PID(float error, float prevErr, float& intErr, float P, float I, float D, float sat_min, float sat_max);

float PID(float error, float prevErr, float intErr, float P, float I, float D, float sat_min, float sat_max);


void controlFlowRate() {    // calculates target pressure and updates system_state.P_target

    // Feed forward part
    float FF_val = system_state.P + controller_state.R*system_state.Q_target - controller_state.R*system_state.Q;

    // PID part
    float P = pid_gains.P_FR;
    float I = pid_gains.I_FR;
    float D = pid_gains.D_FR;
    float error = system_state.Q_target - system_state.Q; // error between target and measured flow rate
    
    float PID_val = PID(error, controller_state.prevFlowErr, controller_state.int_FR, P, I, D, -10000,10000);

    // Update target pressure as sum of feedforward and PID outputs
    system_state.P_target = FF_val + PID_val;

    // Save history for next iteration
    controller_state.prevFlowErr = error;

}



void controlPressure() {    // calculates valve DCs updates system_state.DC1 and system_state.DC2

    float error = system_state.P_target - system_state.P; // error between target and measured pressure

    system_state.DC1 = PID(error, controller_state.prevPressErr, controller_state.int_valv_1, pid_gains.P_V1, pid_gains.I_V1, pid_gains.D_V1, 0, 1);
    system_state.DC2 = PID(-error, -controller_state.prevPressErr, controller_state.int_valv_2, pid_gains.P_V2, pid_gains.I_V2, pid_gains.D_V2, 0, 1);

    // Save history for next iteration
    controller_state.prevPressErr = error;
    controller_state.prevTime = system_state.clock;

}



float PID(float error, float prevErr, float intErr, float P, float I, float D, float sat_min, float sat_max) {
    
    float dt = system_state.clock - controller_state.prevTime;
    if (dt <= 0) return 0; // avoids division by zero

    // Integral
    float integral = intErr + error * dt;
    // Derivative
    float derivative = (error - prevErr) / dt;

    
    // PID output before saturation
    float U = P * error + I * integral + D * derivative;

    // Saturation and anti-windup
    if (U > sat_max) {
        return sat_max;
    }
    else if (U < sat_min) {
        return sat_min;
    }
    else {
        intErr = integral; // Only update integral if not saturated to prevent windup (clamping)
        return U;
    }

}


