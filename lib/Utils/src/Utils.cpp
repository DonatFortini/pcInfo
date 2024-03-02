#include "Utils.h"

// Initialize the SensorData object according to the mode
SensorData *initializeSensorData(int mode)
{
  SensorData *sd;
  switch (mode)
  {
  case CPU:
    sd = new SensorData("CPU", "CPU_TMP:", "C", "CPU_FRQ:", "GHz");
    break;
  case FAN:
    sd = new SensorData("FAN", "FAN_SPD:", "RPM", "FAN_PWR:", "W");
    break;
  case WIFI:
    sd = new SensorData("WIFI", "UPLD:", "Kb/s", "DWLD:", "Kb/s");
    break;
  case RAM:
    sd = new SensorData("RAM", "RAM_USD:", "%", "RAM_FRQ:", "GHz");
    break;
  default:
    sd = new SensorData("ERR", "ERR", "ERR", "ERR", "ERR");
    break;
  }

  return sd;
}

// Read data from serial port and stores it in a the SensorData object passed as parameter
// format of inputString: "sensorName value1,value2;sensorName value1,value2 ..."
void readData(SensorData *data, int mode)
{
  if (Serial.available() > 0)
  {
    int cpuTemp, fanSpeed, fanPower;
    float cpuFreq, ramUsage, ramFreq, upldSpeed, dwldSpeed;
    sscanf(Serial.readString().c_str(), "%d %f %d %d %d %f %f %f", &cpuTemp, &cpuFreq, &fanSpeed, &fanPower, &ramUsage, &ramFreq, &upldSpeed, &dwldSpeed);
    Serial.println(cpuTemp);
  }
}

// Display the data on LCD
void printData(const SensorData *data, LiquidCrystal lcd)
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(data->label1);
  lcd.print(data->value1);
  lcd.print(data->unit1);
  lcd.setCursor(0, 1);
  lcd.print(data->label2);
  lcd.print(data->value2);
  lcd.print(data->unit2);
}
