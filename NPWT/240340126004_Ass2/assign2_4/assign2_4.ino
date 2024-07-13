#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>

#include "DHT.h"

#define DHTPIN 15     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

// Define the BLE service and characteristics
BLEServer *pServer;
BLEService *pService;
BLECharacteristic *pTemperatureCharacteristic;
BLECharacteristic *pHumidityCharacteristic;

// Define the temperature and humidity values
float temperature;
float humidity;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  // Create a BLE device
  BLEDevice::init("Harsha"); // Set device name

  // Create a BLE server
  pServer = BLEDevice::createServer();

  // Create a BLE service
  pService = pServer->createService(BLEUUID((uint16_t)0x180F)); // Health Thermometer service

  // Create a BLE characteristic for temperature
  pTemperatureCharacteristic = pService->createCharacteristic(
    BLEUUID((uint16_t)0x2A6E),  // Temperature characteristic
    BLECharacteristic::PROPERTY_READ
  );

  // Create a BLE characteristic for humidity
  pHumidityCharacteristic = pService->createCharacteristic(
    BLEUUID((uint16_t)0x2A6F),  // Humidity characteristic
    BLECharacteristic::PROPERTY_READ
  );

  // Start the BLE service
  pService->start();

  // Start advertising
  pServer->getAdvertising()->start();

  Serial.println("BLE service started");
  dht.begin();
}

void loop() {
  // Read temperature and humidity values from DHT sensor
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  // Check if readings are valid
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Print the values to the serial monitor
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Update the BLE characteristic values as numeric values
  pTemperatureCharacteristic->setValue(temperature);
  pHumidityCharacteristic->setValue(humidity);

  delay(1000);
}
