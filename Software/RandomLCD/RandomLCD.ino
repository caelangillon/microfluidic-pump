#include <LiquidCrystal_I2C.h>

// LCD Setup
LiquidCrystal_I2C lcd(0x27, 16, 2);
String input = "";
byte delta[8] = {
  0b00000,
  0b00000,
  0b00100,
  0b01010,
  0b10001,
  0b11111,
  0b00000,
  0b00000
}; //Delta Symbol

void setup() {
  Serial.begin(115200);

// LCD Setup
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, delta); // store at custom slot 0

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
  lcd.setCursor(0,0);
  lcd.print("Q (uL/min): ");
  lcd.setCursor(3,0);
  lcd.write(byte(0xE4));
  lcd.setCursor(0,1);
  lcd.write(byte(0));
  lcd.setCursor(1,1);
  lcd.print("P (kPa): ");

  lcd.setCursor(12,0);
  float value = random(300, 500) / 100.0;
  lcd.print(value);
  Serial.println(value);

  lcd.setCursor(11,1);
  float value2 = random(-100, 500) / 10.0;
  lcd.print(value2);
  Serial.println(value2);

  delay(200);
  lcd.clear();
}