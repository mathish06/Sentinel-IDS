# SENTINEL 🛡️
### Passive WiFi Intrusion Detection System (P-IDS)

![Status](https://img.shields.io/badge/Status-Stable-brightgreen)
![Platform](https://img.shields.io/badge/Platform-ESP32-blue)
![Language](https://img.shields.io/badge/Language-C%2B%2B-orange)
![License](https://img.shields.io/badge/License-MIT-green)
![Framework](https://img.shields.io/badge/Framework-PlatformIO%20%2F%20Arduino-purple)

**Sentinel** is a portable, standalone hardware device designed to monitor 802.11 WiFi traffic in real-time. Built on the ESP32 microcontroller, it operates in **promiscuous mode** to analyze raw packets and detect specific attack signatures — without ever connecting to a network.

## 🎯 Project Goal

The primary goal of Sentinel is to provide a **low-cost, Blue Team tool** for detecting **Deauthentication Flooding attacks** and potential **Evil Twin** attempts. Unlike software-based solutions (like Wireshark) that require a laptop, Sentinel is a pocket-sized "watchdog" for your wireless environment.

## ⚙️ Features

- **Passive Sniffing:** Operates transparently with no IP address or network association.
- **Channel Hopping:** Cyclically scans 2.4GHz WiFi channels (1–13) to cover the full spectrum.
- **Attack Detection:** Identifies abnormal bursts of Management Frames (Deauth/Disassoc packets).
- **Simulation Mode:** Differentiates real attacks from lab-generated test frames (custom MAC signature).
- **Visual Feedback:**
  - **OLED Display:** Shows current channel, packet rate, real threat count, and simulation test count.
  - **RGB LED:** Color-coded alert system — 🔵 Blue = Boot, 🟢 Green = Under Attack, 🔴 Red = Safe (inverted for visibility).
- **Portable:** Powered by any generic 5V USB power bank.

## 🛠️ Hardware Stack

| Component | Model | Notes |
| :--- | :--- | :--- |
| **MCU** | ESP32-WROOM-32U (DevKit V1) | External antenna for extended range |
| **Display** | 0.96" OLED SSD1306 | I2C interface |
| **LED** | WS2812B Addressable RGB (NeoPixel) | 1 pixel |
| **Power** | 5000mAh USB Power Bank | Generic 5V |

## 🔌 Wiring (Pinout)

| Component | ESP32 Pin | Description |
| :--- | :--- | :--- |
| **OLED SDA** | GPIO 21 | I2C Data |
| **OLED SCL** | GPIO 22 | I2C Clock |
| **NeoPixel Data** | GPIO 15 | WS2812B Signal |
| **VCC** | VIN (5V) | Power from USB |
| **GND** | GND | Ground |

## 🚀 Getting Started

### Prerequisites

- [Visual Studio Code](https://code.visualstudio.com/)
- [PlatformIO](https://platformio.org/) IDE Extension

### Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/mathish06/Sentinel-IDS.git
   cd Sentinel-IDS
   ```

2. Open the folder in VS Code.

3. Connect your ESP32 via USB.

4. Upload the firmware using PlatformIO:
   - Click the **PlatformIO logo** in the left sidebar.
   - Select **Pick a task… → General → Upload**.

PlatformIO will automatically download all required libraries (`Adafruit SSD1306`, `Adafruit GFX`, `Adafruit NeoPixel`) and flash the ESP32.

## 📦 Dependencies

Managed automatically via PlatformIO:

```ini
lib_deps =
    adafruit/Adafruit SSD1306 @ ^2.5.7
    adafruit/Adafruit GFX Library @ ^1.11.5
    adafruit/Adafruit NeoPixel
```

## ⚠️ Legal Disclaimer

**This project is strictly for educational and defensive (Blue Team) purposes.**

The device is designed to *detect* wireless attacks, not to initiate them. Monitoring wireless networks without explicit authorization from the network owner may be illegal in your jurisdiction. The author assumes no responsibility for any misuse of this software or hardware design.

---

*Project created as part of the Epitech First Year Hub module.*