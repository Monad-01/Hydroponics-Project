#include <DFRobot_DHT20.h>
#include <U8g2lib.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define TdsSensorPin A1
#define VREF 5.0              // analog reference voltage(Volt) of the ADC
#define SCOUNT  30            // sum of sample point

int analogBuffer[SCOUNT];     // store the analog value in the array, read from ADC
int analogBufferTemp[SCOUNT];
int analogBufferIndex = 0;
int copyIndex = 0;

float averageVoltage = 0;
float tdsValue = 0;
float waterTemperature = 20;


DFRobot_DHT20 dht20;

char tbuffer[6];  // Reusable character array for temperature (adjust based on actual precision needed)
char hbuffer[6];  // Reusable character array for humidity (adjust based on actual precision needed)

LiquidCrystal_I2C lcd(0x27, 20, 4);

// median filtering algorithm
int getMedianNum(int bArray[], int iFilterLen){
  int bTab[iFilterLen];
  for (byte i = 0; i<iFilterLen; i++)
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
  if ((iFilterLen & 1) > 0){
    bTemp = bTab[(iFilterLen - 1) / 2];
  }
  else {
    bTemp = (bTab[iFilterLen / 2] + bTab[iFilterLen / 2 - 1]) / 2;
  }
  return bTemp;
}

void setup() {
  dht20.begin();
  // u8g2.begin();
  Serial.begin(9600);
  pinMode(TdsSensorPin,INPUT);
  
  lcd.begin();
  lcd.backlight();
}

//Idea: Maybe alter the libaries I am using to do the calculations and store the things I really need.
void loop() {
  ///Ugly code for the tds sensor
  static unsigned long analogSampleTimepoint = millis();
  if(millis()-analogSampleTimepoint > 40U){     //every 40 milliseconds,read the analog value from the ADC
    analogSampleTimepoint = millis();
    analogBuffer[analogBufferIndex] = analogRead(TdsSensorPin);    //read the analog value and store into the buffer
    analogBufferIndex++;
    if(analogBufferIndex == SCOUNT){ 
      analogBufferIndex = 0;
    }
  }   
  
  static unsigned long printTimepoint = millis();
  if(millis()-printTimepoint > 800U){
    printTimepoint = millis();
    for(copyIndex=0; copyIndex<SCOUNT; copyIndex++){
      analogBufferTemp[copyIndex] = analogBuffer[copyIndex];
      
      // read the analog value more stable by the median filtering algorithm, and convert to voltage value
      averageVoltage = getMedianNum(analogBufferTemp,SCOUNT) * (float)VREF / 1024.0;
      
      //temperature compensation formula: fFinalResult(25^C) = fFinalResult(current)/(1.0+0.02*(fTP-25.0)); 
      float compensationCoefficient = 1.0+0.02*(waterTemperature-25.0);
      //temperature compensation
      float compensationVoltage=averageVoltage/compensationCoefficient;
      
      //convert voltage value to tds value
      tdsValue=(133.42*compensationVoltage*compensationVoltage*compensationVoltage - 255.86*compensationVoltage*compensationVoltage + 857.39*compensationVoltage)*0.5;
      
      //Serial.print("voltage:");
      //Serial.print(averageVoltage,2);
      //Serial.print("V   ");
      Serial.print("TDS Value:");
      Serial.print(tdsValue,0);
      Serial.println("ppm");
    }
  }

  ///

  lcd.clear();
  float t = dht20.getTemperature() * 9/5 + 32;  // Temperature
  float h = dht20.getHumidity();  // Humidity

  // Convert float to char arrays with reduced precision
  dtostrf(t, 5, 1, tbuffer);
  dtostrf(h, 5, 1, hbuffer);

  // u8g2.clearBuffer();  // Clear internal memory
  // u8g2.setFont(u8g2_font_ncenB08_tr);  // Smaller font

  // Print temperature and humidity directly to the display
  // u8g2.setCursor(0, 20);
  lcd.print(F("Temp: "));
  lcd.print(tbuffer);
  lcd.print(F(" F"));

  // u8g2.setCursor(0, 40);
  lcd.setCursor(0,1);
  lcd.print(F("Humid: "));
  lcd.print(hbuffer);

  // u8g2.sendBuffer();  // Transfer internal memory to the display
  delay(5000);
}