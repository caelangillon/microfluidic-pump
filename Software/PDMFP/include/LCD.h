#ifndef LCD_H
#define LCD_H

#include <Arduino.h>

void setupLCD();
void updateLCD(float pressure, float flowRate, float pressure_target, float flowRate_target, float DC1, float DC2, float time);

#endif // LCD_H