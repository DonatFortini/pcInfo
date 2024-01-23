#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>
#include <LiquidCrystal.h>

typedef enum
{
  CPU = 0,
  FAN,
  WIFI,
  RAM,
} Mode;

class SensorData
{
public:
  const char *value1;
  const char *value2;
  const char *sensorName;
  const char *label1;
  const char *unit1;
  const char *label2;
  const char *unit2;

  SensorData(const char *sName, const char *l1, const char *u1, const char *l2, const char *u2)
      : value1("N/A"), value2("N/A"), sensorName(sName), label1(l1), unit1(u1), label2(l2), unit2(u2)
  {
  }

  ~SensorData()
  {
  }
};

SensorData *initializeSensorData(int mode);
void readData(SensorData *data, int mode);
void printData(const SensorData *data, LiquidCrystal lcd);
String *split(String str, String separator);

#endif