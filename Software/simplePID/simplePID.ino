#include "HX711.h"

#define HX_DT  8
#define HX_SCK 9

HX711 scale;

// PID VARIABLES //

float Kp_pos = 0.005;
float Ki_pos = 0.001;
float Kd_pos = 0;

float Kp_neg = 0.009;
float Ki_neg = 0.0001;
float Kd_neg = 0;

float prevTime;
float prevError = 0; // stores previous error for derivative
float integral = 0; // stores current accumulated integral of error

float output;

// VARIABLES //

float calibration_factor = 36.93;

float dutyA;   // Pin 11
float dutyB;   // Pin 3

//
//
//
//  SETUP
//
//
//

void setup() {

  Serial.begin(9600);

  // HX711
  scale.begin(HX_DT, HX_SCK);
  scale.set_scale(calibration_factor);
  scale.tare();  // zero the sensor

  // Set PWM pins
  pinMode(3, OUTPUT);
  pinMode(11, OUTPUT);

  // Timer2 Fast PWM, prescaler 8 (~7.8kHz)
  TCCR2A = (1 << COM2A1) | (1 << COM2B1) |
           (1 << WGM21)  | (1 << WGM20);

  TCCR2B = (1 << CS21);

  prevTime = millis();

  // Hang until "start" is sent through serial
  String input = "";
  while (true) {
    if (Serial.available() > 0) {
      input = Serial.readStringUntil('\n');
      input.trim(); //removes whitespace from string
    }
    
    if (input == "Start") {
      Serial.println("Starting PID controller...");
      break;
    } else {
      Serial.println("Type 'Start' to begin controller.");
    }
    delay(300); //prevents serial flooding
  }
}

//
//
//
//  LOOP
//
//
//

void loop() {
  unsigned long now = millis();
  float dt = (now - prevTime) / 1000.0;
  prevTime = now;

  // Setpoint and target pressure
  float P_target = 100000;  // Setpoint in same units as calibration

  // Read pressure sensor
  float P_meas = scale.get_units(3); 

  // Determine error
  float error = P_target - P_meas;

  // Use PID controllers, then set PWM
  if (error >= 0) {
    float output_pos = PID_pos(error, dt);
    dutyA = constrain(output_pos, 0, 100);
    dutyA = map(dutyA, 0, 100, 60, 100);
  } else {
    PID_neg(error, dt);
    float output_neg = PID_pos(error, dt);
    dutyB = constrain(output_neg, 0, 100);
    dutyB = map(dutyB, 0, 100, 60, 100);
  }

  updatePWM();

  Serial.println()
}

//
//
//
//  EXTRA FUNCTIONS
//
//
//

float PID_pos(float error, float dt) {
  float proportional = Kp_pos * error;
  if (dutyA >= 100 || dutyB >= 100) {
    integral = 0;
  } else {
    integral += error * dt;
  }
  float derivative = Kd_pos * ((error - prevError) / dt);

  prevError = error;

  return output = proportional + (Ki_pos * integral) + derivative;
}

float PID_neg(float error, float dt) {
  float proportional = Kp_neg * error;
  if (dutyA >= 100 || dutyB >= 100) {
    integral = 0;
  } else {
    integral += error * dt;
  }
  float derivative = Kd_neg * ((error - prevError) / dt);

  prevError = error;

  return output = proportional + (Ki_neg * integral) + derivative;
}

void updatePWM() {
  OCR2A = (uint8_t)((constrain(dutyA, 0, 100) / 100.0) * 255.0);
  OCR2B = (uint8_t)((constrain(dutyB, 0, 100) / 100.0) * 255.0);
}