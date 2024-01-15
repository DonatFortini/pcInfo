#include <Arduino.h>
#include <LiquidCrystal.h>

const int buttonPin = 7;
int mode = 0;
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
    mode = (mode + 1) % 2;
  lcd.clear();
  switch (mode)
  {
  case 0:
    printCPU(readCPU());
    break;
  case 1:
    lcd.print("Hello World!");
    break;
  default:
    break;
  }

  delay(2000);
}

float *readCPU()
{
  static float cpuData[2];
  if (Serial.available())
  {
    String inputString = Serial.readStringUntil('\n');
    inputString.trim();
    // string format: "TempintFloatFreq" -> 273.41
    float Temp = inputString.substring(0, 2).toFloat();
    float Freq = inputString.substring(2).toFloat();
    cpuData[0] = Temp;
    cpuData[1] = Freq;
  }
  else // the bash script has a problem
  {
    cpuData[0] = -1;
    cpuData[1] = -1;
  }
  return cpuData;
}

void printCPU(float *CPU_Info)
{
  lcd.print("CPU Temp:");
  lcd.setCursor(9, 0);
  lcd.print((int)CPU_Info[0]);
  lcd.setCursor(12, 0);
  lcd.print("C");

  lcd.setCursor(0, 1);
  lcd.print("CPU Freq:");
  lcd.setCursor(9, 1);
  lcd.print(CPU_Info[1]);
  lcd.setCursor(13, 1);
  lcd.print("GHz");
}
