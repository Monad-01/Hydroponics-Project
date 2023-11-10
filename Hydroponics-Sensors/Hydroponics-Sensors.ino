  #define LED 6
 
void setup() {
  // put your setup code here, to run once:
  pinMode(LED,OUTPUT);    //Sets the pinMode to Output 
}
 
void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, HIGH); //Sets the voltage to high 
  delay(1000);					   //Waits for 1000 milliseconds 
  digitalWrite(LED, LOW);  //Sets the voltage to low
  delay(1000);             //Waits for 1000 milliseconds 
}