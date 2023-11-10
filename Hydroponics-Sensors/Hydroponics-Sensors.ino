  	
#include "Arduino_SensorKit.h"
  
#define LED 6
#define Environment Environment_I2C

void setup() {
  Wire.begin();
  // Environment.begin();

  Oled.begin();
  Oled.setFlipMode(true); // Sets the rotation of the screen

  
  // Serial.begin(9600);
  

  

  // pinMode(LED,OUTPUT);    //Sets the pinMode to Output 
}
 
void loop() {
  // put your main code here, to run repeatedly:
  // digitalWrite(LED, HIGH); //Sets the voltage to high 
  // delay(1000);					   //Waits for 1000 milliseconds 
  // digitalWrite(LED, LOW);  //Sets the voltage to low
  // delay(1000);             //Waits for 1000 milliseconds 

  // Serial.print("Temperature = ");
  // Serial.print(Environment.readTemperature());
  // Serial.println(" C");
  
  // Serial.print("Humidity = ");
  // Serial.print(Environment.readHumidity());
  // Serial.println(" %");

  int random_value = analogRead(A0);
 
  Oled.setFont(u8x8_font_chroma48medium8_r);
  Oled.setCursor(0, 33);
  Oled.print("Temp");
  // Oled.print(Environment.readTemperature());
  Oled.print(" CDS");
  Oled.refreshDisplay();
  
  delay(1000); // Delay for OLED display update
}