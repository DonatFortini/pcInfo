#include <Arduino.h>
#include <LiquidCrystal.h>

#define BUTTON_PIN 7
#define MODE_NUM 4

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
  const int bound;

  SensorData(const char *v1, const char *v2, const char *sName, const char *l1, const char *u1, const char *l2, const char *u2, int b)
      : value1(v1), value2(v2), sensorName(sName), label1(l1), unit1(u1), label2(l2), unit2(u2), bound(b)
  {
  }

  ~SensorData()
  {
  }
};

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
Mode mode = CPU;
SensorData *sensorData;
void readData(SensorData &data);
void printData(const SensorData &data);
String *split(String str, String separator);

void setup()
{
  lcd.begin(16, 2);
  Serial.begin(9600);
  analogWrite(10, 90);
  DDRD &= ~(1 << BUTTON_PIN); // set button pin as input
}

void loop()
{
  if (PIND & (1 << BUTTON_PIN))
    mode = static_cast<Mode>((mode + 1) % MODE_NUM);
  // rajouter un interupt -> PCINTO pour le bouton

  lcd.clear();
  switch (mode)
  {
  case CPU:
    sensorData = new SensorData("", "", "CPU", "CPU_TMP:", "C", "CPU_FRQ:", "GHz", 3);
    break;
  case FAN:
    sensorData = new SensorData("", "", "FAN", "FAN_SPD:", "RPM", "FAN_PWR:", "W", 3);
    break;
  case WIFI:
    sensorData = new SensorData("", "", "WIFI", "UPLD:", "Kb/s", "DWLD:", "Kb/s", 3);
    break;
  case RAM:
    sensorData = new SensorData("", "", "RAM", "RAM_USD:", "%", "RAM_FRQ:", "GHz", 3);
    break;
  default:
    break;
  }
  readData(*sensorData);
  printData(*sensorData);
  delete sensorData;
  delay(1000);
}

// Read data from serial port to return Sensors Data
void readData(SensorData &data)
{
  Serial.println("readData");
  if (Serial.available() > 0)
  {
    Serial.println("serial available");
    String inputString = Serial.readStringUntil('\n');
    inputString.trim();
    Serial.println(inputString);
    String *sensorsData = split(inputString, ";");
    Serial.println(sensorsData[mode]);
    // format of inputString: "sensorName vrustalue1,value2;sensorName value1,value2 ..."
    String *sensorData = split(sensorsData[mode], " ");
    data.value1 = sensorData[1].substring(0, sensorData[1].indexOf(",")).c_str();
    data.value2 = sensorData[1].substring(sensorData[1].indexOf(",") + 1).c_str();
  }
}

// Display the data on LCD
void printData(const SensorData &data)
{
  lcd.setCursor(0, 0);
  lcd.print(data.label1);
  lcd.print(data.value1);
  lcd.print(data.unit1);
  lcd.setCursor(0, 1);
  lcd.print(data.label2);
  lcd.print(data.value2);
  lcd.print(data.unit2);
}

// Split a string by separator and return an array of string
String *split(String str, String separator)
{
  int count = 0, i = 0, len = (int)str.length();
  int separatorIndex[len];
  while (count < len)
  {
    separatorIndex[i] = str.indexOf(separator, count);
    count = separatorIndex[i] + 1;
    i++;
  }
  String *result = new String[i];
  for (int j = 0; j < i; j++)
    result[j] = str.substring(separatorIndex[j], separatorIndex[j + 1]);
  return result;
}
