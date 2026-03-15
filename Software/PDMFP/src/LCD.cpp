#include "LCD.h"
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "sharedData.h"

LiquidCrystal_I2C lcd(0x27, 16, 4);

void setupLCD() {
    lcd.init();
    lcd.backlight();
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Screen Ready");  
    delay(1000); // Display the message for 1 second
    lcd.clear();
    return;
}

void updateLCD() {

    float pressure = system_state.P;
    float flowRate = system_state.Q;
    float pressure_target = system_state.P_target;
    float flowRate_target = system_state.Q_target;
    float DC1 = system_state.DC1;
    float DC2 = system_state.DC2;
    float time = system_state.clock;

    lcd.setCursor(0, 0);
    lcd.print("P: ");
    lcd.print(pressure, 1); // Print pressure with 1 decimal place
    lcd.print(" kPa");

    lcd.setCursor(7, 0);
    lcd.print("Q: ");
    lcd.print(flowRate, 1); // Print flow rate with 1 decimal place
    lcd.print(" uL/min");

    lcd.setCursor(0, 1);
    lcd.print("Set P: ");
    lcd.print(pressure_target); // Print target pressure
    lcd.print(" kPa");

    lcd.setCursor(7, 1);
    lcd.print("Set Q: ");
    lcd.print(flowRate_target); // Print target flow rate
    lcd.print(" uL/min");

    lcd.setCursor(0, 2);
    lcd.print("Valve 1 Duty Cycle: ");
    lcd.print(DC1); // Print valve 1 duty cycle
    lcd.print(" %");

    lcd.setCursor(7, 2);
    lcd.print("Valve 2 Duty Cycle: ");
    lcd.print(DC2); // Print valve 2 duty cycle
    lcd.print(" %");

    lcd.setCursor(0, 3);
    lcd.print("Current runtime: ");
    lcd.print(time, 2); // Print runtime with 2 decimal places
    lcd.print(" s");
    return;
    
}