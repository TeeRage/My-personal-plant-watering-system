//Soil sensor library seesaw
#include "Adafruit_seesaw.h"

Adafruit_seesaw ss;

int led = LED_BUILTIN; //ESP32 feather built in led
int delay_ms = 5000; //Loop delay in milliseconds
const float moistTresholdStart = 400; //Moisture value treshold for watering pump to activate
const float moistTresholdStop = 600; //Moisture value treshold for watering pump to stop

void setup() {

  //Select serial connection
  Serial.begin(115200);
  
  // set built in LED to be an output pin
  pinMode(led, OUTPUT);

  Serial.println("Starting...");

  //check that soil sensor library can be found
  if (!ss.begin(0x36)) {
    Serial.println("ERROR! seesaw not found");
    while(1) delay(1);
  } else {
    Serial.print("seesaw started! version: ");
    Serial.println(ss.getVersion(), HEX);
  }
}

void loop() {
  float tempC = ss.getTemp(); //Read soil sensor temperature value in celsius
  uint16_t capread = ss.touchRead(0); //Read moisture values from sensor, between 320-650

  //Read moisture and temperature values from sensor, from between 0-650
  
  Serial.print("Temperature: "); Serial.print(tempC); Serial.println(" C");  
  Serial.print("Capacitive: "); Serial.println(capread);

  //Light up the led if soil is dry and turn it off if wet enough
  if(capread < moistTresholdStart){
    digitalWrite(led, HIGH); // turn LED on
  }else{
    digitalWrite(led, LOW); //turn LED off
  }
  
  delay(delay_ms); //Loop measurements
}
