# Real-Time Finger Detection & IoT Display System

This is an interactive fun sorta project that I've made to mess around with computer vision and esp32. It tracks hand gestures and counts raised fingers using a computer vision Python script, transmits the data in real-time via **UDP packets over Wi-Fi**, and displays the live count on a hardware **ESP32 microcontroller** connected to an **SSD1306 OLED screen**.

---

## 🚀 Features

* **Computer Vision Tracking:** Utilizes Google MediaPipe and Python to detect hand landmarks and count raised fingers in real-time through your webcam.
* **Wireless UDP Communication:** Streams finger count data instantly over a local 2.4 GHz Wi-Fi network using the lightweight UDP protocol.
* **Microcontroller Processing:** Powered by an ESP32 Dev Module handling network sockets and hardware displays.
* **Hardware Visual Feedback:** Renders the live finger count dynamically onto a 128x64 I2C SSD1306 OLED display.

---

## 🛠️ Hardware Requirements

* 1x ESP32 Development Module
* 1x SSD1306 128x64 OLED Display (I2C interface)
* 4x Male-to-Female Jumper Wires
* 1x USB Cable for programming the ESP32
* Computer with a webcam and Python installed

---

## 🔌 Wiring Diagram

Connect the SSD1306 OLED display to the ESP32 using the standard hardware I2C pins:

| OLED Pin | ESP32 Pin | Description |
| :--- | :--- | :--- |
| **GND** | **GND** | Ground |
| **VCC** | **3V3** | Power Supply (3.3V) |
| **SCL** | **GPIO 22** | I2C Serial Clock |
| **SDA** | **GPIO 21** | I2C Serial Data |

---

## 📦 Software & Library Dependencies

### Arduino IDE Libraries
Ensure you have the following libraries installed via the Arduino IDE Library Manager:
* `Adafruit_SSD1306`
* `Adafruit_GFX`
* `Wire` (Built-in)
* `WiFi` (Built-in)
* `WiFiUdp` (Built-in)

### Python Dependencies
* `opencv-python`
* `mediapipe`

---

## ⚙️ Configuration & Setup

### 1. Configure the ESP32 Code
1. Open your Arduino sketch (`.ino`) file.
2. Replace the placeholder Wi-Fi credentials with your network details:
   ```cpp
   const char* ssid = "wifi_name";
   const char* password = "wifi_password";
