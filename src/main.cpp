#include <Arduino.h>
#include <LiquidCrystal.h>

const int buttonPin = 7;

enum Mode
{
  CPU = 0,
  FAN,
  WIFI,
};

const int modeNum = 3;
Mode mode = CPU;

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
float *readCPU();
void printCPU(float *CPU_Info);

void setup()
{
  lcd.begin(16, 2);
  analogWrite(10, 90);
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
}

void loop()
{
  if (digitalRead(buttonPin) == HIGH)
    mode = static_cast<Mode>((mode + 1) % modeNum);

  lcd.clear();

  switch (mode)
  {
  case CPU:
    printCPU(readCPU());
    break;
  case FAN:
    lcd.print("Hello World!");
    break;
  case WIFI:
    lcd.print("World!");
    break;
  default:
    break;
  }

  delay(2000);
}

float *readCPU()
{
  static float cpuData[2] = {-1, -1};
  if (Serial.available())
  {
    String inputString = Serial.readStringUntil('\n');
    inputString.trim();

    float Temp = inputString.substring(0, 2).toFloat();
    float Freq = inputString.substring(2).toFloat();
    cpuData[0] = Temp;
    cpuData[1] = Freq;
  }
  return cpuData;
}

void printCPU(float *CPU_Info)
{
  lcd.print("CPU Temp:");
  lcd.setCursor(9, 0);
  lcd.print(static_cast<int>(CPU_Info[0]));
  lcd.setCursor(12, 0);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("CPU Freq:");
  lcd.setCursor(9, 1);
  lcd.print(CPU_Info[1]);
  lcd.setCursor(13, 1);
  lcd.print("GHz");
}
