//Import libraries
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

//Define UUID for service and characteristic. Generated with https://www.uuidgenerator.net/
#define SERVICE_UUID        "e24feb68-ce7e-4f13-8200-5cbe78b56eb0"
#define CHARACTERISTIC_UUID "8cb7ca91-1fd1-4a58-bdae-52958d4ffa94"

BLEServer *pServer;
BLEService *pService;
BLECharacteristic *pCharacteristic;
BLEAdvertising *pAdvertising;

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE server");

  BLEDevice::init("ESP32"); //creates BLE device with the name ESP32
  pServer = BLEDevice::createServer(); //Set device as a server
  pService = pServer->createService(SERVICE_UUID); //create a service

  //Set characteristics for the service
  pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE
                                       );
  
  //Soil sensor values can be inserted here
  pCharacteristic->setValue("Hello World");
  pService->start(); //Start server
  
  // BLEAdvertising *pAdvertising = pServer->getAdvertising();  // this is still working for backward compatibility
  pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising(); //Start edvertising
  Serial.println("Characteristic defined");
}

void loop() {
  //main code here, this is just for printing hello world
  //std::string value = pCharacteristic->getValue();
  //Serial.print("The new characteristic value is: ");
  //Serial.println(value.c_str());
  delay(5000);
}
