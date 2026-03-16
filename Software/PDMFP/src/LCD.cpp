#include "LCD.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "sharedData.h"

LiquidCrystal_I2C lcd(0x27, 16, 4);

// Helper: print a right-padded field to overwrite old characters
static void printPadded(const char* str, uint8_t totalWidth) {
    uint8_t len = strlen(str);
    lcd.print(str);
    for (uint8_t i = len; i < totalWidth; i++) lcd.print(' ');
}

void setupLCD() {
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  Screen Ready  ");
    delay(1000);
    lcd.clear();

    // Print static labels once
    lcd.setCursor(0, 0); lcd.print("P:       Q:     ");
    lcd.setCursor(0, 1); lcd.print("Pt:      Qt:    ");
    lcd.setCursor(0, 2); lcd.print("DC1:     DC2:   ");
    lcd.setCursor(0, 3); lcd.print("T:              ");
}

void updateLCD() {
    char buf[9]; // Temp buffer for formatted numbers

    // Row 0: P and Q values
    lcd.setCursor(3, 0);
    dtostrf(system_state.P, 6, 1, buf);   // width=6, 1 decimal
    printPadded(buf, 6);

    lcd.setCursor(11, 0);
    dtostrf(system_state.Q, 5, 1, buf);
    printPadded(buf, 5);

    // Row 1: Target P and Q
    lcd.setCursor(4, 1);
    dtostrf(system_state.P_target, 5, 1, buf);
    printPadded(buf, 5);

    lcd.setCursor(12, 1);
    dtostrf(system_state.Q_target, 4, 1, buf);
    printPadded(buf, 4);

    // Row 2: Duty cycles
    lcd.setCursor(5, 2);
    dtostrf(system_state.DC1, 4, 1, buf);
    printPadded(buf, 4);

    lcd.setCursor(13, 2);
    dtostrf(system_state.DC2, 3, 1, buf);
    printPadded(buf, 3);

    // Row 3: Clock time
    lcd.setCursor(3, 3);
    dtostrf(system_state.clock, 8, 2, buf);
    printPadded(buf, 8);
}