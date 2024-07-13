#include <BLEDevice.h>
#include <BLEScan.h>

const char* knownDeviceMac = "48:9d:d1:8e:89:68";
const int ledPin = 2;

BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    void onResult(BLEAdvertisedDevice advertisedDevice) {
      String deviceAddress = advertisedDevice.getAddress().toString();
      if (deviceAddress.equals(knownDeviceMac)) {
        digitalWrite(ledPin, HIGH);
        Serial.println("Known device found! Turning on LED.");
      } else {
        digitalWrite(ledPin, LOW);
        Serial.println("Unknown device found. Turning off LED.");
      }
    }
};

void setup() {
  Serial.begin(115200);
  BLEDevice::init("Harsha");
  pinMode(ledPin, OUTPUT);
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->setInterval(100);
  pBLEScan->setWindow(99);
}

void loop() {
  pBLEScan->start(50, false);
  delay(1000);
}
