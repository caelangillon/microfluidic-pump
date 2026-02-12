// Feed-forward PID controller

// DATA STORAGE //
const float T = 273.7;

const float p_atm = 101500; //bar
const float p_hydro = 0;

const float r = 7; // is this the gas constant? or the resistance?
const float r_c = 5;
const float r_rout = 5;

const float v_tot = 0.001;
const float v_l0 = 0;

const float q_target = 20; //this can later be added so that python updates this live (not hardcoded)

unsigned long prevTime = 0;

struct PID1 {
  float error;
  float prevError = 0;
  float prevIntegral = 0;
  
  float proportional;
  float integral;
  float derivative;

  const float Kp = 0.1;
  const float Ki = 0.1;
  const float Kd = 0.1;
  float out;
} pid1;

struct PID2 {
  float error;
  float prevError = 0;
  float prevIntegral = 0;
  
  float proportional;
  float integral;
  float derivative;

  const float Kp = 0.1;
  const float Ki = 0.1;
  const float Kd = 0.1;
  float out;
} pid2;

// PID CONTROLLERS //
float PID_1(float q_target, float q_out, float dt) {
  pid1.error = q_target - q_out;

  pid1.proportional = pid1.Kp * pid1.error;
  pid1.integral = pid1.Ki * (pid1.prevIntegral + (dt * pid1.error));
  pid1.derivative = pid1.Kd * ((pid1.error - pid1.prevError) / dt); // linear assumption (euler method)

  pid1.prevError = pid1.error;
  pid1.prevIntegral = pid1.integral;

  return pid1.out = pid1.proportional + pid1.integral + pid1.derivative;
}

float PID_2(float p_target, float p, float dt) {
  pid2.error = p_target - p;

  pid2.proportional = pid2.Kp * pid2.error;
  pid2.integral = pid2.Ki * (pid2.prevIntegral + (dt * pid2.error));
  pid2.derivative = pid2.Kd * ((pid2.error - pid2.prevError) / dt); // linear assumption (euler method)

  pid2.prevError = pid2.error;
  pid2.prevIntegral = pid2.integral;

  return pid2.out = pid2.proportional + pid2.integral + pid2.derivative;
}

// VOLUME OUT FUNCTION //
float v_integral(float q_out, float dt) {
  static float v_last = 0; // just initialises value to zero, doesn't reset every function call

  float v_out = v_last + q_out * dt;
  v_last = v_out;

  return v_out;
}

// AFFECTIVE AREA AND DRIVER CURRENT FUNCTION //
float valve_profile(float mdot_target, float p, float p_in, float p_out) {
  if (mdot_target > 0) {
    float G3 = (sqrt(7) * mdot_target * sqrt(r * T)) / (7 * p * sqrt((p/p_in)^(10/7) - (p/p_in)^(12/7)));
    // to be continued
  } else {
    float G4 = (sqrt(7) * mdot_target * sqrt(r * T)) / (7 * p_out * sqrt((p_out/p)^(10/7) - (p_out/p)^(12/7)));
    // to be continued
  }
}

// SENSOR MEASUREMENT //
float frs() {
  float q_out = 3;
  return q_out;
}

float prs() {
  float p = 3;
  return p;
}

// CONTROLLER EXECUTION //
void setup() {
// Nothing added here yet
}

void loop() {
  // Determine dt for controller
  unsigned long now = millis();
  float dt = (now - prevTime) / 1000.0;
  prevTime = now;

  // Read sensors
  float q_out = frs();  // to be finished still
  float p = prs();      // to be finished still

  // Determine target pressure
  float G1 = p_atm - p_hydro + q_out * (r_c + r_rout);
  float feedforward = G1 * q_target;

  float p_target = PID_1(q_target, q_out, dt) + feedforward;

  // Determine rate of change of target pressure
  float pdot_target = PID_2(p_target, p, dt);

  // Determine mass flow rate target
  float v_out = v_integral(q_out, dt);
  float G2 = (pdot_target * (v_tot - v_l0 + v_out) + q_out * p) / (r * T);
  float mdot_target = pdot_target * G2;

  // Determine the affective area and required driver current
  float p_pin = 0.5; //what is this?
  float p_out = 0.5; //what is this?

  float current = valve_profile(mdot_target, p, p_pin, p_out);
}