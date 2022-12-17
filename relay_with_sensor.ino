//Soil sensor library seesaw
#include "Adafruit_seesaw.h"

Adafruit_seesaw ss;

const int relayPin = 13; //Pin 13 for relay
int ledPin = LED_BUILTIN; //ESP32 feather built in led
int delay_ms = 4000; //Loop delay in milliseconds
const float moistTresholdStart = 450; //Moisture value treshold for watering pump to activate

void setup() {

  //Select serial connection
  Serial.begin(115200);
  
  pinMode(relayPin, OUTPUT); // Set pin 13 to output for relay
  pinMode(ledPin, OUTPUT); // set built in LED to be an output pin

  Serial.println("Starting...");

  // Check that soil sensor library can be found
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
  uint16_t capread = ss.touchRead(0); //Read moisture values from sensor, between 320-850

  //Read moisture and temperature values from sensor, from between 0-850  
  //Serial.print("Temperature: "); Serial.print(tempC); Serial.println(" C");  
  //Serial.print("Capacitive: "); Serial.println(capread);

  //Turn water pump ON if soil is dry
  if(capread < moistTresholdStart){
    digitalWrite(ledPin, HIGH); // Turn LED ON
    digitalWrite(relayPin, HIGH); // Turn relay ON
    
  }else{ // Turn water pump OFF if soil is wet enough
    digitalWrite(ledPin, LOW); //turn LED OFF
    digitalWrite(relayPin, LOW); //Turn Relay OFF
  }
  
  delay(delay_ms); //Loop measurements
}
