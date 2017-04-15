#include <ESP8266WiFi.h>

// Digital pins for WeMos D1
static const uint8_t D[] = {3, 1, 16, 5, 4, 14, 12, 13, 0, 2, 15};

void setup() {
  Serial.begin(9600);
  Serial.println();

  WiFi.begin("network-name", "pass-to-network");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  ;
}