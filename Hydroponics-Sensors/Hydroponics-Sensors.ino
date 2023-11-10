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
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);  // High-speed I2C

char tbuffer[6];  // Reusable character array for temperature (adjust based on actual precision needed)
char hbuffer[6];  // Reusable character array for humidity (adjust based on actual precision needed)

void setup() {
  dht20.begin();
  u8g2.begin();
}

//Idea: Maybe alter the libaries I am using to do the calculations and store the things I really need.
void loop() {
  float t = dht20.getTemperature() * 9/5 + 32;  // Temperature
  float h = dht20.getHumidity();  // Humidity

  // Convert float to char arrays with reduced precision
  dtostrf(t, 5, 1, tbuffer);
  dtostrf(h, 5, 1, hbuffer);

  u8g2.clearBuffer();  // Clear internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr);  // Smaller font

  // Print temperature and humidity directly to the display
  u8g2.setCursor(0, 20);
  u8g2.print(F("Temp: "));
  u8g2.print(tbuffer);
  u8g2.print(F(" F"));

  u8g2.setCursor(0, 40);
  u8g2.print(F("Humid: "));
  u8g2.print(hbuffer);

  u8g2.sendBuffer();  // Transfer internal memory to the display
  delay(1000);
}