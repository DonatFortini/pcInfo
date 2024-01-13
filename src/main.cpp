#include <Arduino.h>
#include <LiquidCrystal.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);


void setup() {
  lcd.begin(16, 2);
  lcd.print("CPU Temp:");
}

void loop() {
  lcd.setCursor(9, 0);
  lcd.print(random(20, 30));
  lcd.setCursor(12, 0);
  lcd.print("C");
  
  lcd.setCursor(0, 1);
  lcd.print("CPU Freq:");
  lcd.setCursor(9, 1);
  lcd.print(4.98);
  lcd.setCursor(13, 1);
  lcd.print("GHz");
  
  delay(1000);
}
