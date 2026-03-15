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
  return false;
}

bool sendToUI() {
// Send system state back to UI
    Serial.write((uint8_t*)&system_state, sizeof(system_state));
return true;
}