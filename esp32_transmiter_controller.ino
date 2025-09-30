#include <esp_now.h>
#include <WiFi.h>

// Joystick and button pin definitions
#define JOYSTICK_X1_PIN 34
#define JOYSTICK_Y1_PIN 35
#define JOYSTICK_X2_PIN 32
#define JOYSTICK_Y2_PIN 33
#define BUTTON1_PIN 25
#define BUTTON2_PIN 26
#define BUTTON3_PIN 27
#define BUTTON4_PIN 14

// Structure to hold the outgoing data
typedef struct struct_message {
  int joystickX1;
  int joystickY1;
  int joystickX2;
  int joystickY2;
  int button1;
  int button2;
  int button3;
  int button4;
} struct_message;

struct_message outgoingData;

// Peer MAC address of the receiver ESP32 (replace with your slave ESP32 MAC address)
uint8_t receiverMAC[] = {0x24, 0x6F, 0x28, 0xA1, 0xF0, 0xBD}; // Example MAC, replace with actual

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(115200);

  // Initialize joystick and button pins as inputs
  pinMode(JOYSTICK_X1_PIN, INPUT);
  pinMode(JOYSTICK_Y1_PIN, INPUT);
  pinMode(JOYSTICK_X2_PIN, INPUT);
  pinMode(JOYSTICK_Y2_PIN, INPUT);
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);
  pinMode(BUTTON3_PIN, INPUT_PULLUP);
  pinMode(BUTTON4_PIN, INPUT_PULLUP);

  // Set ESP32 as Wi-Fi station
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register peer (receiver ESP32)
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, receiverMAC, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;

  // Add peer
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // Read joystick and button inputs
  outgoingData.joystickX1 = analogRead(JOYSTICK_X1_PIN);
  outgoingData.joystickY1 = analogRead(JOYSTICK_Y1_PIN);
  outgoingData.joystickX2 = analogRead(JOYSTICK_X2_PIN);
  outgoingData.joystickY2 = analogRead(JOYSTICK_Y2_PIN);

  // Buttons are active low, so we invert the readings
  outgoingData.button1 = !digitalRead(BUTTON1_PIN);
  outgoingData.button2 = !digitalRead(BUTTON2_PIN);
  outgoingData.button3 = !digitalRead(BUTTON3_PIN);
  outgoingData.button4 = !digitalRead(BUTTON4_PIN);

  // Send data to receiver
  esp_now_send(receiverMAC, (uint8_t *)&outgoingData, sizeof(outgoingData));

  // Debugging: Print the values being sent
  Serial.print("Joystick X1: "); Serial.println(outgoingData.joystickX1);
  Serial.print("Joystick Y1: "); Serial.println(outgoingData.joystickY1);
  Serial.print("Joystick X2: "); Serial.println(outgoingData.joystickX2);
  Serial.print("Joystick Y2: "); Serial.println(outgoingData.joystickY2);
  Serial.print("Button 1: "); Serial.println(outgoingData.button1);
  Serial.print("Button 2: "); Serial.println(outgoingData.button2);
  Serial.print("Button 3: "); Serial.println(outgoingData.button3);
  Serial.print("Button 4: "); Serial.println(outgoingData.button4);

  delay(100); // Add a small delay between transmissions
}
