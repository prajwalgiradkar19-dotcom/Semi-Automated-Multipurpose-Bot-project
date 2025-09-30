# Semi-Automated-Multipurpose-Bot-project

# ESP32 master & slave 
frist instal Arduino IDE.
instal esp32 driver - CP10X_Universal_Windows_driver on windows.
instal all requried Liberies on Arduion IDE - ESP32Servo-master,WifiEspNow-main,WifiEspNow-main.
then coppy the code file - esp32_reciver_modul.ino,esp32_transmiter_controller.ino.
for get mac address of esp32 - get_esp32_mac_address.ino, example - 00:1A:7D:DA:71:13
Peer MAC address of the receiver ESP32 (replace with your slave ESP32 MAC address)
*uint8_t receiverMAC[] = {0x00, 0x1A, 0x7D, 0xDA, 0x71, 0x13}; // Example MAC, replace with actual*

# ESP32-cam 
To connect the esp32-cam module with your any device to access wirless view
connect esp32-cam and select your module type for example-*CAMERA_MODEL_AI_THINKER*
//#define CAMERA_MODEL_M5STACK_PSRAM
//#define CAMERA_MODEL_M5STACK_WITHOUT_PSRAM
//#define CAMERA_MODEL_M5STACK_PSRAM_B
//#define CAMERA_MODEL_WROVER_KIT
which one if you have module just uncomment it

Replace with your network credentials
const char *ssid = "your ssid";
const char *password = "your password";

To view your cammera you will downlode telegram app for Web url-ip address(Esp32_alert)
in telegram surch IDBot and click on */start* bot provid (P.S.Your ID: 123456789)
insurt in this line of code *#define CHAT_ID "123456789"*

Telegram Bot Credentials
#define BOTtoken "7999794710:AAHiwcITvgrIDNQmPEKZqJMm3-Xa8daEIoc"  // your Bot Token (Get from Botfather)
#define CHAT_ID "123456789"
#define PART_BOUNDARY "123456789000000000000987654321"
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
bool pirTriggered = false;

# Required component
1.	Robotic Arm 4-axis
2.	Car kit
3.	ESP 32 wroom DV modue
4.	ESP 32 CAM Module
5.	Jumper Wires 
6.	IR proximity sensor
7.	Buck converter
8.	Ultrasonic sensor
9.	Pan-tilt kit
10.	Battery pack 12v DC
11.	Servo motor
12.	Motor Driver
13.	Joysticks
14.	PCB bord
15.	On off switch
