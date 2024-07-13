#include <WiFi.h>

const char* ssid = "ESP32_Harsha";
const char* password = "Harsha123";

WiFiServer server(80);

const int ledPin = 2;  // LED pin on AP ESP32

void setup() {
  Serial.begin(115200);

  // Set up WiFi AP
  WiFi.softAP(ssid, password);

  // Set up LED pin as output
  pinMode(ledPin, OUTPUT);

  // Start server
  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    String request = client.readStringUntil('\r');
    Serial.println(request);

    if (request.indexOf("/ledon")!= -1) {
      digitalWrite(ledPin, HIGH);
    } else if (request.indexOf("/ledoff")!= -1) {
      digitalWrite(ledPin, LOW);
    }

    client.stop();
  }
}
