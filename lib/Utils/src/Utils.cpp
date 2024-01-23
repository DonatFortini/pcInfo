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
    String inputString = "";
    while (Serial.available())
    {
      char c = Serial.read();
      inputString += c;
    }
    String *dataArray = split(inputString, ";");
    String *finalData = split(dataArray[mode], "_");
    data->value1 = finalData[1].substring(0, finalData[1].indexOf(",")).c_str();
    data->value2 = finalData[1].substring(finalData[1].indexOf(",") + 1).c_str();
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

// Split a string by separator and return an array of string 
//similar to the split function in Python
String *split(String str, String separator)
{
  int count = 0, i = 0, len = (int)str.length(), start = 0;
  int separatorIndex[len];
  while (count < len)
  {
    separatorIndex[i] = str.indexOf(separator, count);
    if (separatorIndex[i] == -1)
      break;
    count = separatorIndex[i] + separator.length();
    ++i;
  }
  String *result = new String[i + 1];
  for (int j = 0; j < i; ++j)
  {
    result[j] = str.substring(start, separatorIndex[j]);
    start = separatorIndex[j] + separator.length();
  }
  result[i] = str.substring(start);
  return result;
}
