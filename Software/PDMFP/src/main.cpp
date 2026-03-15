#include <Arduino.h>
#include "UIComs.h"
#include "PressureSensor.h"
#include "FlowRateSensor.h"
#include "SharedData.h"
#include "LCD.h"
#include "Controller.h"
#include "propValve.h"
#include <HX711.h>

ControlParams ctrl_params;
PidGains pid_gains;
SystemState system_state;

void setup() {

  // Setup serial communication
  Serial.begin(115200); // i think i remember seeing that 9600 is req. in a datasheet somewhere but could be wrong. ensure this aligns with platformio.ini
  //Serial.setTimeout(100); // Set timeout for serial read operations to 100ms

  // Setup sensors
  setupPressureSensor();
  setupFlowRateSensor();

  // Setup LCD
  setupLCD();
}

void loop() {

  // Read UI inputs
  readFromUI(); // check if control parameters or PID gains have been changed

  // System state
  system_state.clock = millis() / 1000.0; // In seconds
  updatePressure();
  updateFlowRate();

  // Controller
  system_state.DC1 = PID_V1(system_state.P_target, system_state.P);
  system_state.DC2 = PID_V2(system_state.Q_target, system_state.Q);

  while (!true) {
    resetControllers();
  } // Optional controller reset function, could be triggered by UI?

  // Proportional Valves
  updatePropValves(system_state.DC1, system_state.DC2);

  // LCD Screen
  updateLCD(system_state.P, system_state.Q, system_state.P_target, system_state.Q_target, system_state.DC1, system_state.DC2, system_state.clock);

  // send system state back to computer for monitoring
  sendToUI();
}