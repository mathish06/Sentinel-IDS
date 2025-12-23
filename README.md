# SENTINEL 🛡️
### Passive Wifi Intrusion Detection System (P-IDS)

![Status](https://img.shields.io/badge/Status-In%20Development-yellow)
![Platform](https://img.shields.io/badge/Platform-ESP32-blue)
![Language](https://img.shields.io/badge/Language-C%2B%2B-orange)

**Sentinel** is a portable, standalone hardware device designed to monitor 802.11 WiFi traffic in real-time. Built on the ESP32 microcontroller, it operates in **promiscuous mode** to analyze raw packets and detect specific attack signatures without ever connecting to a network.

## 🎯 Project Goal
The primary goal of Sentinel is to provide a low-cost, "Blue Team" tool for detecting **Deauthentication Flooding attacks** and potential **Evil Twin** attempts. Unlike software-based solutions (like Wireshark) that require a laptop, Sentinel is a pocket-sized "watchdog" for your wireless environment.

## ⚙️ Features
* **Passive Sniffing:** Operates transparently without IP address or network association.
* **Channel Hopping:** Cyclically scans 2.4GHz WiFi channels (1-13) to cover the full spectrum.
* **Attack Detection:** Identifies abnormal bursts of Management Frames (Deauth/Disassoc packets).
* **Visual Feedback:**
    * **OLED Display:** Shows current channel, packet rate, and threat status.
    * **RGB LED:** Color-coded alert system (Green = Safe, Red = Under Attack).
* **Portable:** Powered by a generic 5V power bank.

## 🛠️ Hardware Stack
* **MCU:** ESP32-WROOM-32U (DevKit V1) with external antenna for extended range.
* **Display:** 0.96" OLED (SSD1306 driver, I2C).
* **Indicators:** WS2812B Addressable RGB LED (NeoPixel).
* **Power:** 5000mAh USB Power Bank.

## 🚀 Getting Started

### Prerequisites
* [Visual Studio Code](https://code.visualstudio.com/)
* [PlatformIO](https://platformio.org/) Extension

### Installation
1.  Clone the repository:
    ```bash
    git clone [https://github.com/TonUsername/Sentinel.git](https://github.com/TonUsername/Sentinel.git)
    cd Sentinel
    ```
2.  Open the folder in VS Code.
3.  Connect your ESP32 via USB.
4.  Upload the code using PlatformIO:
    * Click the **PlatformIO logo** on the left sidebar.
    * Click **Pick a task...** > **General** > **Upload**.

## 🔌 Wiring (Pinout)

| Component | Pin ESP32 | Description |
| :--- | :--- | :--- |
| **OLED SDA** | GPIO 21 | I2C Data |
| **OLED SCL** | GPIO 22 | I2C Clock |
| **NeoPixel** | GPIO 15 | Data In |
| **VCC** | VIN (5V) | Power |
| **GND** | GND | Ground |

## ⚠️ Legal Disclaimer
**This project is for educational and defensive purposes only.**
The device is designed to detect attacks, not to initiate them. Usage of this tool for monitoring networks without authorization may be illegal in your jurisdiction. The author assumes no responsibility for misuse of this software.

---
*Project created as part of the Epitech First Year Hub module.*