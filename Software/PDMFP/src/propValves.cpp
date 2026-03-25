#include "propValves.h"
#include "sharedData.h"
#include <Arduino.h>

void setupValvePWMs() {
    pinMode(3, OUTPUT);
    pinMode(11, OUTPUT);

    // Reset Timer2 control registers
    TCCR2A = 0;
    TCCR2B = 0;

    // Non-inverting PWM on OC2A (pin 11) and OC2B (pin 3) (COM2A1 + COM2B1) and Set Fast PWM mode (WGM21 + WGM20)
    TCCR2A = _BV(COM2A1) | _BV(COM2B1) | _BV(WGM21) | _BV(WGM20);

    // Prescaler = 8  ->  7812.5 Hz
    TCCR2B = _BV(CS21);

    // Duty cycle (0–255)
    OCR2B = 0;   // 0% (pin 3)
    OCR2A = 0;   // 0% (pin 11)
}

void updateValvePWMs() {
    float dc1_pwm = (round(system_state.DC1*256)-1); // convert 0-1 duty cycle to 0-255 for OCR2B (pin 3)
    float dc2_pwm = (round(system_state.DC2*256)-1); // convert 0-1 duty cycle to 0-255 for OCR2A (pin 11)

    OCR2B = (uint8_t)constrain(dc1_pwm, 0, 255); // set duty cycle for pin 3
    OCR2A = (uint8_t)constrain(dc2_pwm, 0, 255); // set duty cycle for pin 11
}