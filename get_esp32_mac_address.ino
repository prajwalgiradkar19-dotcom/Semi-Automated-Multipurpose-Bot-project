#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  delay(1000);

  // Get MAC address
  String mac = WiFi.macAddress();
  Serial.println("ESP32 MAC Address: " + mac);
}

void loop() {
  // Nothing here
}