#include <Arduino.h>
#include "UIComs.h"
#include "PressureSensor.h"
#include "FlowRateSensor.h"
#include "SharedData.h"
#include <HX711.h>

ControlParams ctrl_params;
PidGains pid_gains;
SystemState system_state;


void setup() {

  // initialize serial communication for UI
  Serial.begin(115200);
  // Serial.setTimeout(100); // Set timeout for serial read operations to 100ms

  // setup pressure sensor
  setupPressureSensor();
  // setup flow rate sensor
  // setupFlowRateSensor();

}

void loop() {

  // check if control parameters or PID gains have been changed
  readFromUI(); 

  // Update system state from sensors
  system_state.clock = millis() / 1000.0; // Update system clock in seconds
  updatePressure();
  // updateFlowRate();


  // send system state back to computer for monitoring
  sendToUI();
}







