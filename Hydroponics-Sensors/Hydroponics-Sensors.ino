#include <DFRobot_DHT20.h>
#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

DFRobot_DHT20 dht20;
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);  // High speed I2C

void setup() {
  // Serial.begin(9600);
  dht20.begin();

  u8g2.begin();
}
 
void loop() {
 
  float t = dht20.getTemperature() * 9/5 + 32; //Temperature

  float h = dht20.getHumidity(); //Humidity

  char tbuffer[10];
  char hbuffer[10];

  dtostrf(t, 6, 2, tbuffer);
  dtostrf(h, 6, 2, hbuffer);

  u8g2.clearBuffer();                   // Clear internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);   // Font

  String tempString = "Temperature: " + String(tbuffer) + " F";
  String humString = "Humidity: " + String(hbuffer) + " %RH";

  // Display temp/humidity results to the monitor
  u8g2.setCursor(0, 20);
  u8g2.print(tempString);
  u8g2.setCursor(0,40);
  u8g2.print(humString);

  u8g2.sendBuffer();      // transfer internal memory to the display
  delay(1000); 
}