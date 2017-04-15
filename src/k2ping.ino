#include <ESP8266WiFi.h>
#include <Wire.h>
#include <LiquidCrystal.h>

// Digital pins for WeMos D1
static const uint8_t D[] = {3, 1, 16, 5, 4, 14, 12, 13, 0, 2, 15};

// LCD Keypad Shield for Arduino
LiquidCrystal lcd(D[8], D[9], D[4], D[5], D[6], D[7]);

void setup() {
  lcd.begin(16, 2);

  WiFi.begin("network-name", "pass-to-network");

  lcd.print("Connecting");
  lcd.setCursor(0, 1);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

    static uint8_t i = 0;
    lcd.setCursor((i %= 32) % 16, 1);
    if (i < 16) {
      lcd.write(0xFF);
      i++;
    } else if (i < 32) {
      lcd.print(" ");
      i++;
    }
  }

  lcd.clear();
  lcd.print("Connected");
  lcd.setCursor(0, 1);
  lcd.print(WiFi.localIP());
}

void loop() {
  ;
}
