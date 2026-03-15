#include <Arduino.h>
#include "sharedData.h"
#include "UIComs.h"
#include "LCD.h"
#include "pressureSensor.h"
#include "flowRateSensor.h"
#include "targetGenerator.h"
#include "controllers.h"
#include "propValves.h"


controlParams ctrl_params;
pidGains pid_gains;
systemState system_state;
controllerState controller_state;

void setup() {

  // Setup serial communication
  Serial.begin(9600); // i think i remember seeing that 9600 is req. in a datasheet somewhere but could be wrong. ensure this aligns with platformio.ini
  //Serial.setTimeout(100); // Set timeout for serial read operations to 100ms

  // Setup sensors
  setupPressureSensor();
  // setupFlowRateSensor();

  // // Setup LCD
  // setupLCD();
}

void loop() {

  // Read UI inputs
  if (readFromUI()) {  // check if control parameters or PID gains have been changed from UI and update ctrl_params and pid_gains accordingly
    // Update control targets
    if (ctrl_params.selection == 0) {
      // turnOffSystem(); // to be implemented: depressurizes then closes valves and stops any control actions when UI is closed
    }
    else if (ctrl_params.selection == 1) {
      resetTargets(); // resets timer for stepped/sinusoidal control
    }
    else if (ctrl_params.selection == 2) {
      controller_state.prevFlowErr = 0; // reset PID history for flow rate controller
      resetTargets(); // resets timer for stepped/sinusoidal control
    }
  }
  


  // Update system states from sensors and timer
  system_state.clock = millis() / 1000.0; // In seconds
  updatePressure(); // reads from sensor and updates system_state.P
  // updateFlowRate(); // reads from sensor and updates system_state.Q



  // Controllers
  updateTarget();         // updates target flowrate or pressure based on control selection, type and parameters (e.g. stepped, sinusoidal, etc.)
  if (ctrl_params.selection == 2) {
    controlFlowRate();      // to be implemented: calculates target pressure and updates system_state.P_target
  }
  controlPressure();      // to be implemented: calculates valve DCs updates system_state.DC1 and system_state.DC2


  // // Set valve duty cycles based on controller outputs
  // updatePropValves(); // to be implemented: sets PWM duty cycles based on system_state.DC1 and system_state.DC2

  // while (!true) {
  //   resetControllers();
  // } // Optional controller reset function, could be triggered by UI?
 

  // // LCD Screen
  // updateLCD(); // updates LCD display with current system state values (pressure, flow rate, targets, valve DCs, time)

  // send system state back to computer for monitoring
  sendToUI();
}