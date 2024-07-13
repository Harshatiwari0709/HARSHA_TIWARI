#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
  

// --------- BLE -----------------
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define PIN_LED 2
#define PIN_BUTTON 0
#define DEBOUNCE_DELAY 300

bool currentLEDState = true;
unsigned long lastDebounceTime = 0;

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;


//------------------ BLE support funcs() ----------------
class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      String value = pCharacteristic->getValue();
      //std::string value = pCharacteristic->getValue();

      if (value.length() > 0) {
        Serial.println("*********************************");
        Serial.print("New value: ");
        for (int i = 0; i < value.length(); i++)
          Serial.print(value[i]);
          if (value[0]== '1')
            digitalWrite(PIN_LED,HIGH);
            else 
              digitalWrite(PIN_LED,LOW);
        Serial.println();
        Serial.println("led is on");
        Serial.println("*****************************************************************");
      }
    }
};

/*/ ------------ DHTxx Setup() ---------------
void vDHT11Setup()
{
  dht.begin();
};*/

// ------------ Bluetooth Setup() ---------------
void vBLESetup()
{
  
  // Create the BLE Device and advertise with name "PRN_xxx"
  BLEDevice::init("Harsha");
  pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE |
                                        BLECharacteristic::PROPERTY_NOTIFY |
                                        BLECharacteristic::PROPERTY_INDICATE
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());

  pCharacteristic->setValue("Hello harsha here");

  
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
  Serial.println("BLE initiated");
};



// ----------- setup() ----------------------
void setup() {
  Serial.begin(115200);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);

  vBLESetup();
  //vDHT11Setup();  

}

// ----------------- loop() ---------------------
void loop() {
}
