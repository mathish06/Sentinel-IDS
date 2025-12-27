#include <Arduino.h>
#include <WiFi.h>

void setup() {
  Serial.begin(115200);
  Serial.println("Sentinel System Starting...");
  WiFi.mode(WIFI_STA);
  Serial.println("Wifi Stack Loaded.");
}

void loop() {
  Serial.println("System alive...");
  delay(1000);
}
