#include <DFRobot_DHT20.h>
#include <U8g2lib.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define TdsSensorPin A1
#define VREF 5.0              // Analog reference voltage(Volt) of the ADC
#define SCOUNT  30            // Sum of sample points

// Variables for TDS sensor
int analogBuffer[SCOUNT];      // Store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0;
int copyIndex = 0;
float averageVoltage = 0;
float tdsValue = 0;
float waterTemperature = 20;

DFRobot_DHT20 dht20;

// Reusable character arrays for temperature and humidity
char tbuffer[6];
char hbuffer[6];

LiquidCrystal_I2C lcd(0x27, 20, 4);

// Median filtering algorithm for smoothing readings
int getMedianNum(int bArray[], int iFilterLen){
  int bTab[iFilterLen];
  for (byte i = 0; i < iFilterLen; i++)
    bTab[i] = bArray[i];
  int i, j, bTemp;
  for (j = 0; j < iFilterLen - 1; j++) {
    for (i = 0; i < iFilterLen - j - 1; i++) {
      if (bTab[i] > bTab[i + 1]) {
        bTemp = bTab[i];
        bTab[i] = bTab[i + 1];
        bTab[i + 1] = bTemp;
      }
    }
  }
  if ((iFilterLen & 1) > 0) {
    bTemp = bTab[(iFilterLen - 1) / 2];
  } else {
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  }
  return bTemp;
}

void setup() {
  // Initialize sensors and serial communication
  dht20.begin();
  Serial.begin(9600);
  pinMode(TdsSensorPin, INPUT);

  // Initialize LCD display
  lcd.begin();
  lcd.backlight();
}

void loop() {

  // TDS sensor readings (TBH I don't understand it that well, but it works...)
  static unsigned long analogSampleTimepoint = millis();
  if (millis() - analogSampleTimepoint > 40U) {
    analogSampleTimepoint = millis();
    analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin); // Read the analog value from the sensor
    analogBufferIndex++;
    if (analogBufferIndex == SCOUNT) {
      analogBufferIndex = 0; // Reset the index when the buffer is full
    }
  }

  static unsigned long printTimepoint = millis();
  if (millis() - printTimepoint > 800U) {
    printTimepoint = millis();
    for (copyIndex = 0; copyIndex < SCOUNT; copyIndex++) {
      analogBufferTemp[copyIndex] = analogBuffer[copyIndex];

      // Read the analog value more stable by the median filtering algorithm, and convert to voltage value
      averageVoltage = getMedianNum(analogBufferTemp, SCOUNT) * (float)VREF / 1024.0;
      float compensationCoefficient = 1.0 + 0.02 * (waterTemperature - 25.0);
      float compensationVoltage = averageVoltage / compensationCoefficient;

      // Convert voltage value to TDS value using a formula
      tdsValue = (133.42 * compensationVoltage * compensationVoltage * compensationVoltage - 255.86 * compensationVoltage * compensationVoltage + 857.39 * compensationVoltage) * 0.5;

      // Print TDS value to the serial monitor
      Serial.print("TDS Value:");
      Serial.print(tdsValue, 0);
      Serial.println("ppm");
    }
  }

  // Display sensor readings on LCD
  lcd.clear();
  float t = dht20.getTemperature() * 9/5 + 32;  // Temperature
  float h = dht20.getHumidity();  // Humidity

  // Convert float to char arrays with reduced precision
  dtostrf(t, 5, 1, tbuffer);
  dtostrf(h, 5, 1, hbuffer);

  // Display temperature, humidity, and tds on LCD
  lcd.print(F("Temp: "));
  lcd.print(tbuffer);
  lcd.print(F(" F"));

  lcd.setCursor(0, 1);
  lcd.print(F("Humid: "));
  lcd.print(hbuffer);

  lcd.setCursor(0, 2);
  lcd.print(F("TDS: "));
  lcd.print(tdsValue, 0);
  lcd.print(F(" ppm"));

  // Delay for 5 seconds before the next loop iteration
  delay(5000);
}
