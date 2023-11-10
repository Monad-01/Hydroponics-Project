#include <DFRobot_DHT20.h>
#include <U8g2lib.h>

DFRobot_DHT20 dht20;
U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* SCL= */ 2, /* SDA= */3, /* reset=*/ U8X8_PIN_NONE);

void setup() {
  // Serial.begin(9600);
  // dht20.begin();

  
}
 
void loop() {
  // //Get ambient temperature
  // Serial.print("Temperature:"); Serial.print(dht20.getTemperature());Serial.print("C ");
  // //Get relative humidity
  // Serial.print("Humidity:"); Serial.print(dht20.getHumidity()*100);Serial.println(" %RH");
  
  delay(10000);
}