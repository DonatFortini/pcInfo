#include "Utils.h"

const char *enumToString(Mode mode)
{
  switch (mode)
  {
  case CPU:
    return "CPU";
  case FAN:
    return "FAN";
  case WIFI:
    return "WIFI";
  case RAM:
    return "RAM";
  default:
    return "ERR";
  }
}

// Initialize the SensorData object based on the mode
SensorData *initializeSensorData(int mode)
{
  SensorData *sd;
  switch (mode)
  {
  case CPU:
    sd = new SensorData("CPU", "CPU_TMP:", "C", "CPU_FRQ:", "GHz");
    break;
  case FAN:
    sd = new SensorData("FAN", "SPD:", "RPM", "FAN_PWR:", "W");
    break;
  case WIFI:
    sd = new SensorData("WIFI", "UP:", "Kb/s", "DL:", "Kb/s");
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

// Read data from serial port and store it in the SensorData object passed as a parameter
// The format of inputString: "sensorName value1,value2;sensorName value1,value2 ..."
void readData(int mode, LiquidCrystal_I2C lcd, SensorData *data)
{
  String values[8];
  String previousValue1 = data->value1;
  String previousValue2 = data->value2;

  while (Serial.available())
  {
    String inputString = Serial.readString();
    int index = 0;
    int start = 0;
    int end = inputString.indexOf(' ');
    while (end != -1)
    {
      values[index] = inputString.substring(start, end);
      start = end + 1;
      end = inputString.indexOf(' ', start);
      index++;
    }
    values[index] = inputString.substring(start);
  }

  int m = (mode % 4) * 2;

  if (strcmp(enumToString(static_cast<Mode>(mode)), data->sensorName) != 0 || strcmp(previousValue1.c_str(), values[m].c_str()) || strcmp(previousValue2.c_str(), values[m + 1].c_str()))
  {
    delete data;
    data = initializeSensorData(mode);
    switch (mode)
    {
    case CPU:
      data->value1 = values[0].c_str();
      data->value2 = values[1].c_str();
      break;
    case FAN:
      data->value1 = values[2].c_str();
      data->value2 = values[3].c_str();
      break;
    case WIFI:
      data->value1 = values[4].c_str();
      data->value2 = values[5].c_str();
      break;
    case RAM:
      data->value1 = values[6].c_str();
      data->value2 = values[7].c_str();
      break;
    default:
      break;
    }
    displayData(data, lcd);
  }
}

// Display the data on the LCD
void displayData(const SensorData *data, LiquidCrystal_I2C lcd)
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
