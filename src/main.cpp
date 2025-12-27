#include <esp_wifi.h>
#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

volatile int packet_counter = 0;
int current_channel = 1;

void promiscuous_rx_cb(void* buf, wifi_promiscuous_pkt_type_t type) {
  packet_counter++;
}

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

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();

  esp_wifi_set_promiscuous(true);
  esp_wifi_set_promiscuous_rx_cb(&promiscuous_rx_cb);

  delay(1000);
}

void loop() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("STATUS: SCANNING");
  display.println("~~~~~~~~~~~~~~~~");
  display.print("Packets:   ");
  display.println(packet_counter);
  display.print("Channel: ");
  display.println(WiFi.channel());
  display.display();

  if (packet_counter > 10000){
    packet_counter = 0;
  }

  if (current_channel <= 13) {
    esp_wifi_set_channel(current_channel, WIFI_SECOND_CHAN_NONE);
    current_channel++;
  }
  else {
    current_channel = 1;
  }

  delay(200);
}
