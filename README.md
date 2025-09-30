# Semi-Automated-Multipurpose-Bot-project

This project uses *ESP32* and *ESP32-CAM* modules to build a multipurpose bot with wireless control, camera streaming, and automation features.

# ESP32 Master & Slave Setup

# Step 1: Install Required Software
*Arduino IDE*
*ESP32 Driver for Windows*
CP210x_Universal_Windows_Driver

# Step 2: Install Required Libraries in Arduino IDE

Install these libraries using ZIP Library installation or Library Manager:

ESP32Servo-master
WifiEspNow-main

# Step 3: Add the Code Files

Copy these `.ino` files into Arduino IDE:
esp32_transmitter_controller.ino
esp32_receiver_module.ino`

# Step 4: Get ESP32 MAC Address

Upload the file:
get_esp32_mac_address.ino
Example output:
00:1A:7D:DA:71:13

# Step 5: Add Receiver (Slave) MAC Address in Code
uint8_t receiverMAC[] = {0x00, 0x1A, 0x7D, 0xDA, 0x71, 0x13}; // Replace with your actual MAC


# ESP32-CAM Setup

# Select Your Camera Model
In the code, uncomment the correct module:
#define CAMERA_MODEL_AI_THINKER
Other options (commented by default):
//#define CAMERA_MODEL_M5STACK_PSRAM
//#define CAMERA_MODEL_M5STACK_WITHOUT_PSRAM
//#define CAMERA_MODEL_M5STACK_PSRAM_B
//#define CAMERA_MODEL_WROVER_KIT

# Wi-Fi Credentials
Replace with your own network details:
const char *ssid = "your_ssid";
const char *password = "your_password";

# Telegram Setup (For Camera Alerts)
1. Install Telegram app
2. Search for *IDBot* and type `/start`
3. Copy your *Chat ID* (e.g.,P.S.Your ID: 123456789)
4. Insert it into your code:

# Bot Credentials Example
#define BOTtoken "7999794710:AAHiwcITvgrIDNQmPEKZqJMm3-Xa8daEIoc"  // Replace with your actual token
#define CHAT_ID "123456789"
#define PART_BOUNDARY "123456789000000000000987654321"
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
bool pirTriggered = false;

---

# Required Components

1. Robotic Arm (4-axis)
2. Car Kit
3. ESP32 Wroom Dev Module
4. ESP32-CAM Module
5. Jumper Wires
6. IR Proximity Sensor
7. Buck Converter
8. Ultrasonic Sensor
9. Pan-Tilt Kit
10. 12V DC Battery Pack
11. Servo Motor
12. Motor Driver
13. Joysticks
14. PCB Board
15. On/Off Switch

---
