  	
#include "Arduino_SensorKit.h"
  
#define LED 6
#define Environment Environment_I2C

void setup() {

  Wire.begin();
  pinMode(LED,OUTPUT);    //Sets the pinMode to Output 

  Serial.begin(9600);
  Environment.begin();
}
 
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH); //Sets the voltage to high 
  delay(1000);					   //Waits for 1000 milliseconds 
  digitalWrite(LED, LOW);  //Sets the voltage to low
  delay(1000);             //Waits for 1000 milliseconds 

  Serial.print("Temperature = ");
  Serial.print(Environment.readTemperature()); //print temperature
  Serial.println(" C");
  Serial.print("Humidity = ");
  Serial.print(Environment.readHumidity()); //print humidity
  Serial.println(" %");
  delay(2000);
}