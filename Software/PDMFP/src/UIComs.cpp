#include "UIComs.h"
#include <Arduino.h>

uint8_t readFromUI() {
  static uint8_t msgType = 0x00; // Static variable to store the message type across function calls
  static bool readingParams = false; // Flag to indicate if we are currently reading parameters

  // check for message type
  if (!readingParams) {
    if (Serial.available() < 1) return 0x00; // No message received
    Serial.readBytes((char*)&msgType, 1);
    readingParams = true; 

    // If message type is 0xA0, state message recived by UI, reset system_state.uiMsg to 0x00 after reading
    if (msgType == 0xA0) {
      readingParams = false;
      return 0x00;
    }
  }

  // if message type is 0x01, read control parameters
  if (msgType == 0x01) {
    if (Serial.available() < (int)sizeof(ctrl_params)) return 0x00; // Not enough bytes available
    Serial.readBytes((char*)&ctrl_params, sizeof(ctrl_params));
    readingParams = false;
    return msgType; 
  } 

  // if message type is 0x02, read PID gains
  else if (msgType == 0x02) {
    // Check if bytes are available for reading PID gains
    if (Serial.available() < (int)sizeof(pid_gains)) return 0x00; // Not enough bytes available
    Serial.readBytes((char*)&pid_gains, sizeof(pid_gains));
    readingParams = false;
    return msgType;
  }

  // if message type is  0x03, read calculated resistance
  else if (msgType == 0x03) {
    // Check if bytes are available for reading calculated resistance
    if (Serial.available() < (int)sizeof(controller_state.R)) return 0x00; // Not enough bytes available
    Serial.readBytes((char*)&controller_state.R, sizeof(controller_state.R));
    readingParams = false;
    return msgType;
  }

  readingParams = false;
  msgType = 0x00;
  return 0x00;
}

bool sendToUI() {
// Send system state back to UI
    Serial.write((uint8_t*)&system_state, sizeof(system_state));
return true;
}