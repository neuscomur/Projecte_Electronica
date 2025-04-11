#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

using namespace std;

#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"  // https://www.uuidgenerator.net/
#define CHARACTERISTIC_UUID "7a6ffc80-ef27-4a4d-a8a6-56d93f8feff3"

void setup(){
  Serial.begin(115200);
  Serial.println("Iniciant BLE...");
  BLEDevice::init("NeusFuncionaOk");
  BLEServer *pServer = BLEDevice::createServer();
  BLEService *pService = pServer->createService(SERVICE_UUID);
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ | //podrà ser llegitda amb dispositius que s'hi vinculin
                                         BLECharacteristic::PROPERTY_WRITE //podrà ser escrita per dispositius que s'hi vinculin
                                       );
  string text = "Prova 3";
  pCharacteristic->setValue(text);
  pService->start();
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  BLEDevice::startAdvertising();
  Serial.print("S'ha publicat: ");
  Serial.println(text.c_str());
  // Haurà creat un servidor bt low energy
}

void loop(){
}