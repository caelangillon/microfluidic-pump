#include "controllers.h"

// Currently, the PID outputs are just floats, but maybe we can make it double or long or anything else that might be more accurate? Could be worth trying

float PID(float error, float prevErr, float intErr, float P, float I, float D, float sat_min, float sat_max);

const float R = 80;

void controlFlowRate() {    // calculates target pressure and updates system_state.P_target

    // Feed forward part
    float FF_val = system_state.P + R*system_state.Q_target - R*system_state.Q;

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

    if (error > 0) { // Need to increase pressure, open valve 1
        float P = pid_gains.P_V1;
        float I = pid_gains.I_V1;
        float D = pid_gains.D_V1;
        system_state.DC1 = PID(error, controller_state.prevPressErr, controller_state.int_Press, P, I, D, 0, 1);
        system_state.DC2 = 0; // Ensure valve 2 is closed
    }

    else if (error < 0) { // Need to decrease pressure, open valve 2
        float P = pid_gains.P_V2;
        float I = pid_gains.I_V2;
        float D = pid_gains.D_V2;
        system_state.DC2 = -1 * PID(error, controller_state.prevPressErr, controller_state.int_Press, P, I, D, -1, 0); // negative output for valve 2 since we want to reduce pressure
        system_state.DC1 = 0; // Ensure valve 1 is closed
    }

    else { // Pressure is at target, close both valves
        system_state.DC1 = 0;
        system_state.DC2 = 0;
    }

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





// void resetControllers() {
//     int_FR = 0; lastErr_FR = 0; lastTime_FR = 0;
//     int_V1 = 0; lastErr_V1 = 0; lastTime_V1 = 0;
//     int_V2 = 0; lastErr_V2 = 0; lastTime_V2 = 0;
//     return;
// }