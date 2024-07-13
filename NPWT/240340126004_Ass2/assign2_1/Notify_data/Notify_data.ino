#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include "DHT.h"

#define DHTPIN 15
#define DHTTYPE DHT22

#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

#define BAUD_RATE 115200
#define DELAY_TIME 500

DHT dht(DHTPIN, DHTTYPE);

BLEServer* bleServer = NULL;
BLECharacteristic* temperatureCharacteristic = NULL;
bool deviceConnected = false;
bool oldDeviceConnected = false;
uint32_t value = 0;

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  };

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
  }
};

void initBLE() {
  BLEDevice::init("Harsha");
  bleServer = BLEDevice::createServer();
  bleServer->setCallbacks(new MyServerCallbacks());
}

void initDHT() {
  dht.begin();
}

void setup() {
  Serial.begin(115200);

  initBLE();
  initDHT();

  BLEService* service = bleServer->createService(SERVICE_UUID);
  temperatureCharacteristic = service->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY | BLECharacteristic::PROPERTY_INDICATE
  );

  temperatureCharacteristic->addDescriptor(new BLE2902());
  service->start();

  BLEAdvertising* pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x0);
  BLEDevice::startAdvertising();
  Serial.println("Waiting a client connection to notify...");
}

void loop() {
  float temperature = dht.readTemperature();

  if (isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    delay(DELAY_TIME);
    return;
  }

  String data = "T:" + String(temperature);
  Serial.println("***********************");
  Serial.println("");
  Serial.println(F("% Temperature: "));
  Serial.println(temperature);
  Serial.println("***********************");

  if (deviceConnected) {
    temperatureCharacteristic->setValue(data.c_str());
    temperatureCharacteristic->notify();
    value++;
    delay(DELAY_TIME);
  }

  if (!deviceConnected && oldDeviceConnected) {
    delay(5000);
    bleServer->startAdvertising();
    Serial.println("start advertising");
    oldDeviceConnected = deviceConnected;
  }

  if (deviceConnected &&!oldDeviceConnected) {
    // do stuff here on connecting
    oldDeviceConnected = deviceConnected;
  }
}
