#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


void setup() {
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){
    Serial.println("OLED is not responding");
    while(1);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);

  display.println("Sentinel System");
  display.println("Starting...");

  display.display();

  Serial.println("Sentinel Ready");

  delay(5000);
  display.clearDisplay();
  display.display();
}

void loop() {
  Serial.println("System alive...");
  delay(1000);
  Serial.println("System still alive...");
  delay(1000);
}
