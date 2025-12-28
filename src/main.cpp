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
#define LED_PIN 15
#define NUMPIXELS 1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

volatile int packet_counter = 0;
volatile int real_attacks = 0;
volatile int simu_attacks = 0;
int current_channel = 1;
unsigned long last_attack_time = 0; 

void promiscuous_rx_cb(void* buf, wifi_promiscuous_pkt_type_t type) {
  wifi_promiscuous_pkt_t *packet = (wifi_promiscuous_pkt_t*)buf;
  wifi_header_t *header = (wifi_header_t*)packet->payload;

  uint8_t frame_type = header->frame_control[0];

  bool is_real_attack = (frame_type == 0xC0 || frame_type == 0xA0);
  bool is_simu_attack = (frame_type == 0x08 && header->addr2[0] == 0xAA && header->addr2[1] == 0xBB); //pour la simu en 0X08 avec l'esp anti_sentinel cha1

  if (is_real_attack) {
    real_attacks++;
    last_attack_time = millis();
  }
  else if (is_simu_attack) {
    simu_attacks++;
    last_attack_time = millis();
  }

  packet_counter++;
}

void setup() {
  Serial.begin(115200);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED Fail");
    while(1);
  }

  pixels.begin();
  pixels.setBrightness(20);
  pixels.show();

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  esp_wifi_set_promiscuous(true);
  esp_wifi_set_promiscuous_rx_cb(&promiscuous_rx_cb);

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println("SENTINEL READY");
  display.display();

  pixels.setPixelColor(0, pixels.Color(0, 0, 255));
  pixels.show();
  delay(1000);
}

void loop() {
  esp_wifi_set_channel(current_channel, WIFI_SECOND_CHAN_NONE);

  if (millis() - last_attack_time < 500) {
    pixels.setPixelColor(0, pixels.Color(0, 255, 0));
  } else {
    pixels.setPixelColor(0, pixels.Color(255, 0, 0));
  }
  pixels.show();

  display.clearDisplay();
  display.setCursor(0, 0);
  
  display.print("CH: ");
  display.print(current_channel);
  display.print(" | Pkts: ");
  display.println(packet_counter);
  display.println("----------------");
  display.print("REAL Threat: ");
  display.println(real_attacks);
  display.print("SIMU Test:   ");
  display.println(simu_attacks);
  display.display();

  if (packet_counter > 10000){
    packet_counter = 0;
  }
  current_channel++;
  if (current_channel > 13){
    current_channel = 1;
  }

  delay(150);
}
