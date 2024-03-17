#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <Utils.h>

#define BUTTON_PIN 3
#define MODE_NUM 4

LiquidCrystal_I2C lcd(0x27, 20, 4);
volatile Mode mode = CPU;
SensorData *sensorData;
volatile bool interruptFlag = false;

void changeMode()
{
  if (!interruptFlag) {
    mode = static_cast<Mode>((mode + 1) % MODE_NUM);
    Serial.println("Mode changed");
    interruptFlag = true;
  }
}

void setup()
{
  lcd.init();
  lcd.backlight();
  Serial.begin(9600); // PC INT2
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), changeMode, FALLING);
  sensorData = initializeSensorData(mode);
}

void loop()
{
  if (interruptFlag) {
    interruptFlag = false;
    
  }
  readData(mode, lcd, sensorData);
  delay(1000);
}
