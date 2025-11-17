#include <LiquidCrystal_I2C.h>

// LCD Setup
LiquidCrystal_I2C lcd(0x27, 16, 2);
String input = "";

void setup() {
  Serial.begin(115200);

// LCD Setup
  lcd.init();
  lcd.backlight();

// LCD Startup
  lcd.clear();
  lcd.print("LCD screen is");
  lcd.setCursor(0, 1);
  lcd.print("ready.");
  delay(1500);

// LCD Finish Startup
  lcd.clear();
  lcd.setCursor(0,0);

  if (Serial) {
    lcd.print("Connected");
    delay(1500);
    lcd.clear();
  }
    else {
      lcd.print("No connection...");
      delay(1500);
      lcd.clear();
    }
}

void loop() {
  if (Serial.available() > 0) {
    string c = Serial.read();

    if (isDigit(c) || isAlpha(c) || c == ' ') {
      input += c;
      lcd.clear();
      lcd.print(input);
    } else if (c == '\r' || c == '\n' || c == ']') {
      input = "";
    }
  }
}