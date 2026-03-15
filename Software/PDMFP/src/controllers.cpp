#include "controllers.h"
#include <Arduino.h>
#include "sharedData.h"

// Currently, the PID outputs are just floats, but maybe we can make it double or long or anything else that might be more accurate? Could be worth trying

// Memory for PID loops
static float int_FR = 0, lastErr_FR = 0, lastTime_FR = 0;
static float int_V1 = 0, lastErr_V1 = 0, lastTime_V1 = 0;
static float int_V2 = 0, lastErr_V2 = 0, lastTime_V2 = 0;

float PID_V1(float V1_setpoint, float V1_measured) {
    // only basic PID loop, needs specific changes for anti-windup, saturation, etc.
    
    float dt = system_state.clock - lastTime_V1;
    if (dt <= 0) return 0; // avoids division by zero

    float error = V1_setpoint - V1_measured;
    // Integral
    int_V1 += error * dt;
    // Derivative
    float derivative_V1 = (error - lastErr_V1) / dt;

    // Save history for next iteration
    lastErr_V1 = error;
    lastTime_V1 = system_state.clock;
    
    float U_V1 = pid_gains.P_V1 * error + pid_gains.I_V1 * int_V1 + pid_gains.D_V1 * derivative_V1;
    return constrain(U_V1, 0, 100);
}

float PID_V2(float V2_setpoint, float V2_measured) {
    // only basic PID loop, needs specific changes for anti-windup, saturation, etc.
    
    float dt = system_state.clock - lastTime_V2;
    if (dt <= 0) return 0; // avoids division by zero

    float error = V2_setpoint - V2_measured;
    // Integral
    int_V2 += error * dt;
    // Derivative
    float derivative_V2 = (error - lastErr_V2) / dt;

    // Save history for next iteration
    lastErr_V2 = error;
    lastTime_V2 = system_state.clock;
    
    float U_V2 = pid_gains.P_V2 * error + pid_gains.I_V2 * int_V2 + pid_gains.D_V2 * derivative_V2;
    return constrain(U_V2, 0, 100);
}

float PID_FR(float FR_setpoint, float FR_measured) {
    // only basic PID loop, needs specific changes for anti-windup, saturation, etc.
    
    float dt = system_state.clock - lastTime_FR;
    if (dt <= 0) return 0; // avoids division by zero

    float error = FR_setpoint - FR_measured;
    // Integral
    int_FR += error * dt;
    // Derivative
    float derivative_FR = (error - lastErr_FR) / dt;

    // Save history for next iteration
    lastErr_FR = error;
    lastTime_FR = system_state.clock;
    
    float U_FR = pid_gains.P_FR * error + pid_gains.I_FR * int_FR + pid_gains.D_FR * derivative_FR;
    return constrain(U_FR, 0, 100);
}

void resetControllers() {
    int_FR = 0; lastErr_FR = 0; lastTime_FR = 0;
    int_V1 = 0; lastErr_V1 = 0; lastTime_V1 = 0;
    int_V2 = 0; lastErr_V2 = 0; lastTime_V2 = 0;
    return;
}