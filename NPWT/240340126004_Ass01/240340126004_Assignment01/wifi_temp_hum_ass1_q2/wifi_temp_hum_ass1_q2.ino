#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include "DHT.h"

#define DHTPIN 15     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321

#define PIN_LED 2

const char *ssid = "Harsha123";
const char *password = "HT123";

WiFiServer server(80);
DHT dht(DHTPIN, DHTTYPE);

void setup() {

  pinMode(PIN_LED, OUTPUT);
  
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();

  Serial.println("Server started");
  dht.begin();
}

void loop() {
  WiFiClient client = server.available();  // listen for incoming clients

  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            float humidity = dht.readHumidity();
            float temperature = dht.readTemperature();

            // Check if any reads failed and exit early (to try again).
              if (isnan(humidity) || isnan(temperature) ) {
              Serial.println(F("Failed to read from DHT sensor!"));
              return;
            }

            client.print("Temperature: ");
            client.print(temperature);
            client.print("°C<br>");

            client.print("Humidity: ");
            client.print(humidity);
            client.print("%<br>");


            client.println();
            break;
          } else {
            currentLine = "";
          }
        } else if (c != '\r') {
          currentLine += c;
        }

      }
    }
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
