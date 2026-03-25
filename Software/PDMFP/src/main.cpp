#include <Arduino.h>
#include "sharedData.h"
#include "UIComs.h"
#include "LCD.h"
#include "sensors.h"
#include "targetGenerator.h"
#include "controllers.h"
#include "propValves.h"

// Global variables for system state, controller state, PID gains and control parameters
controlParams ctrl_params;
pidGains pid_gains;
systemState system_state;
controllerState controller_state;


void setup() {

  // Setup serial communication
  Serial.begin(28800); //

  // Setup sensors
  setupPressureSensor();
  setupFlowRateSensor();
  
  // Setup controllers
  setupControllers();

  // Setup valves
  setupValvePWMs();

  // Setup LCD
  // setupLCD();
}


void loop() {

  // Read UI inputs
  int msgType = readFromUI(); // check if any new messages have been received from the UI
  system_state.uiMsg = msgType; // update system state with message type received from UI
  if (msgType == 0x01) {                        // check if control parameters have been changed from UI
    // Update control targets
    if (ctrl_params.selection == 0) {
      // turnOffSystem();                       // to be implemented: depressurizes then closes valves and stops any control actions when UI is closed
      system_state.Q_target = 0;
      system_state.P_target = 0;
    }
    else if (ctrl_params.selection == 1) {
      system_state.Q_target = 0;                // reset flow rate target to 0 for pressure control mode
      resetTargets();                           // resets timer for stepped/sinusoidal control
    }
    else if (ctrl_params.selection == 2) {
      controller_state.prevFlowErr = 0;         // reset PID history for flow rate controller
      resetTargets();                           // resets timer for stepped/sinusoidal control
    }
  }
  else if (msgType == 0x03) {                   // check if calibrated resistance has been sent from UI
    ctrl_params.selection = 2;                  // reset control selection to flow rate
    ctrl_params.type = 1;                       // reset control type to constant
    ctrl_params.param_1 = 0;                    // reset control parameters
    ctrl_params.param_2 = 0;
    ctrl_params.param_3 = 0;
  }
  



  // Update system states from sensors and timer
  system_state.clock = millis() / 1000.0;       // Arduino run time
  updatePressure();                             // reads from sensor and updates system_state.P
  updateFlowRate();                             // reads from sensor and updates system_state.Q


  // Controllers
  updateTarget();                               // updates target flowrate or pressure based on control selection, type and parameters (e.g. stepped, sinusoidal, etc.)
  if (ctrl_params.selection == 2) {
    controlFlowRate();                          // calculates target pressure and updates system_state.P_target if flow rate control is selected
  }
  controlPressure();                            // calculates valve DCs updates system_state.DC1 and system_state.DC2


  // Set valve duty cycles
  updateValvePWMs();                            // sets PWM duty cycles based on system_state.DC1 and system_state.DC2


  // LCD Screen
  // updateLCD();                               // updates LCD display with current system state values (pressure, flow rate, targets, valve DCs, time)


  // Send system state back to computer for monitoring
  sendToUI();                                  // sends current system state back to UI for monitoring
}