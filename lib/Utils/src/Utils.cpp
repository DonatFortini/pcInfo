#include "Utils.h"

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
void readData(int mode, LiquidCrystal lcd, SensorData *data)
{
  String values[8];
  String previousValue1 = data->value1;
  String previousValue2 = data->value2;
  String previousName = data->sensorName;

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

    String newVal1;
    String newVal2;
    SensorData* newData;

    
  }

  if ((strcmp(data->value1, previousValue1.c_str()) != 0 || strcmp(data->value2, previousValue2.c_str()) != 0) || (strcmp(previousName.c_str(), data->sensorName)))
  {
    Serial.println("Displaying data");
    data= new SensorData(data->sensorName, data->label1, data->unit1, data->label2, data->unit2);
    switch (mode)
    {
    case CPU:
       data->value1= values[0].c_str();
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
void displayData(const SensorData *data, LiquidCrystal lcd)
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
