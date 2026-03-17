#include "UIComs.h"
#include <Arduino.h>

bool readFromUI() {
  static uint8_t msgType = 0; // Static variable to store the message type across function calls
  static bool readingParams = false; // Flag to indicate if we are currently reading parameters

  // check for message type
  if (!readingParams) {
    if (Serial.available() < 1) return false;
    Serial.readBytes((char*)&msgType, 1);
    readingParams = true; 
  }

  // if message type is 0x01, read control parameters
  if (msgType == 0x01) {
    if (Serial.available() < (int)sizeof(ctrl_params)) return false;
    Serial.readBytes((char*)&ctrl_params, sizeof(ctrl_params));
    readingParams = false;
    return true; 
  } 

  // if message type is 0x02, read PID gains
  else if (msgType == 0x02) {
    // Check if bytes are available for reading PID gains
    if (Serial.available() < (int)sizeof(pid_gains)) return false;
    Serial.readBytes((char*)&pid_gains, sizeof(pid_gains));
    readingParams = false;
    return true;
  }

  // if message type is  0x03, read calculated resistance
  else if (msgType == 0x03) {
    // Check if bytes are available for reading calculated resistance
    if (Serial.available() < (int)sizeof(controller_state.R)) return false;
    Serial.readBytes((char*)&controller_state.R, sizeof(controller_state.R));
    readingParams = false;
    ctrl_params.selection = 0; // reset control selection to off
    ctrl_params.type = 0; // reset control type to off
    ctrl_params.param_1 = 0; // reset control parameters
    ctrl_params.param_2 = 0;
    ctrl_params.param_3 = 0;
    return true;
  }

  
  return false;
}

bool sendToUI() {
// Send system state back to UI
    Serial.write((uint8_t*)&system_state, sizeof(system_state));
return true;
}