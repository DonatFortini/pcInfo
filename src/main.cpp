#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Utils.h>

#define BUTTON_PIN 3
#define MODE_NUM 4

LiquidCrystal lcd(12, 11, 5, 4, 7, 6);
Mode mode = CPU;
SensorData *sensorData;

void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  analogWrite(10, 90);        // PC INT2
  DDRD &= ~(1 << BUTTON_PIN); // set button pin as input
  PCICR |= B00000100;         // enable interrupt on the group PC INT2
  PCMSK2 |= B00001000;        // enable interrupt on button pin
  sensorData = initializeSensorData(mode);
}

ISR(PCINT2_vect)
{
  mode = static_cast<Mode>((mode + 1) % MODE_NUM);
  sensorData = initializeSensorData(mode);
  readData(sensorData, mode);
  printData(sensorData, lcd);
}

void loop()
{
  readData(sensorData, mode);
  printData(sensorData, lcd);
  delay(2400);
}
