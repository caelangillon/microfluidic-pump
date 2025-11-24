void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(A0, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading = analogRead(A0);
  float voltage = (reading/1024)*5; // Maps ADC ineger value (0 to 1024) from 0V to 5V
  float 

  Serial.print("Voltage (V): ");
  Serial.print(voltage);
  Serial.print(" | ");
  Serial.print("Pressure (kPa): ")
  Serial.println()
}
