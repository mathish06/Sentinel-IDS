#include <esp_wifi.h>
#include <Arduino.h>
#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoPixel.h>
#include "wifi_header.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define LED_PIN 15
#define NUMPIXELS 1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

volatile int packet_counter = 0;
int current_channel = 1;
volatile int attack_counter = 0;

void promiscuous_rx_cb(void* buf, wifi_promiscuous_pkt_type_t type) {
  wifi_promiscuous_pkt_t *packet = (wifi_promiscuous_pkt_t*)buf;
  wifi_header_t *header = (wifi_header_t*)packet->payload;
  uint8_t frame_type = header->frame_control[0];

  if ( (frame_type == 0xC0) || (frame_type == 0xA0) || 
    (frame_type == 0x08 && header->addr2[0] == 0xAA && header->addr2[1] == 0xBB) ) {
    attack_counter++;
  }
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

  pixels.begin();
  pixels.setBrightness(20);
  pixels.show();

  esp_wifi_set_promiscuous(true);
  esp_wifi_set_promiscuous_rx_cb(&promiscuous_rx_cb);

  delay(2000);
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
  display.print("Attacks: ");
  display.println(attack_counter);
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
