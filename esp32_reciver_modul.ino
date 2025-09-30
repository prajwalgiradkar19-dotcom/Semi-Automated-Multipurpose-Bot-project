#include <esp_now.h> 
#include <WiFi.h> 
#include <ESP32Servo.h> 
 
// Motor and sensor pin definitions 
#define MOTOR1_PIN1 19
#define MOTOR1_PIN2 23 
#define MOTOR2_PIN1 18 
#define MOTOR2_PIN2 15 
#define ULTRASONIC_TRIG 12 
#define ULTRASONIC_ECHO 13 
#define IR_SENSOR 22
#define IR_SENSOR 27 
#define DISTANCE_THRESHOLD 30 
 
// Servo pin definitions for the robotic arm 
#define SERVO_BASE_PIN 16 
#define SERVO_SHOULDER_PIN 17 
#define SERVO_ELBOW_PIN 21 
#define SERVO_WRIST_PIN 26
 
// Initialize the servos 
Servo baseServo; 
Servo shoulderServo; 
Servo elbowServo; 
Servo wristServo; 
 
// Servo angle limits 
const int BASE_MIN = 0, BASE_MAX = 180;
const int SHOULDER_MIN = 10, SHOULDER_MAX = 170;
const int ELBOW_MIN = 10, ELBOW_MAX = 170;
const int WRIST_MIN = 180, WRIST_MAX = 20;

// Structure to hold the incoming data from the master ESP32 
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
 
struct_message incomingData; 
 
void setup() { 
  // Initialize serial communication for debugging 
  Serial.begin(115200); 
 
  // Initialize motor and sensor pins 
  pinMode(MOTOR1_PIN1, OUTPUT); 
  pinMode(MOTOR1_PIN2, OUTPUT); 
  pinMode(MOTOR2_PIN1, OUTPUT); 
  pinMode(MOTOR2_PIN2, OUTPUT); 
  pinMode(ULTRASONIC_TRIG, OUTPUT); 
  pinMode(ULTRASONIC_ECHO, INPUT); 
  pinMode(IR_SENSOR, INPUT); 
  pinMode(IR_SENSOR, INPUT);
 
  // Attach servos to their respective pins 
  baseServo.attach(SERVO_BASE_PIN); 
  shoulderServo.attach(SERVO_SHOULDER_PIN); 
  elbowServo.attach(SERVO_ELBOW_PIN); 
  wristServo.attach(SERVO_WRIST_PIN); 
 
  // Set ESP32 as a Wi-Fi station 
  WiFi.mode(WIFI_STA); 
 
  // Initialize ESP-NOW 
  if (esp_now_init() != ESP_OK) { 
    Serial.println("Error initializing ESP-NOW"); 
    return; 
  } 
 
  // Register callback function to receive data 
  esp_now_register_recv_cb(OnDataRecv); 
} 
 
void loop() { 
  // Periodically check the ultrasonic sensor and IR sensor 
  checkUltrasonic(); 
  checkIRSensor(); 
  delay(100); 
} 
 
// Function to check the ultrasonic sensor 
void checkUltrasonic() { 
  long duration; 
   
  // Trigger the ultrasonic sensor 
  digitalWrite(ULTRASONIC_TRIG, LOW); 
  delayMicroseconds(2); 
  digitalWrite(ULTRASONIC_TRIG, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(ULTRASONIC_TRIG, LOW); 
 
  // Measure the echo 
  duration = pulseIn(ULTRASONIC_ECHO, HIGH); 
  int distance = duration * 0.034 / 2; 
 
  // Stop the car if an obstacle is detected 
  if (distance <= DISTANCE_THRESHOLD) { 
    stopCar(); 
    Serial.println("Obstacle detected. Car stopped."); 
  } 
} 
 
// Function to check the IR sensor 
void checkIRSensor() { 
  if (digitalRead(IR_SENSOR) == HIGH || digitalRead(IR_SENSOR) == HIGH) { 
    stopCar(); 
    Serial.println("Ground level hole detected. Car reversing."); 
    reverseCar(); 
  } 
} 
 
// Function to handle received data 
void OnDataRecv(const esp_now_recv_info *info, const uint8_t *data, int len) { 
  // Copy the incoming data to the struct 
  memcpy(&incomingData, data, sizeof(incomingData)); 
 
  // Control the car and robotic arm based on the received data 
  controlCar(); 
  controlRoboticArm(); 
} 
 
// Function to control the car using button inputs 
void controlCar() { 
  if (incomingData.button1 == 1) { 
    // Move forward 
    digitalWrite(MOTOR1_PIN1, HIGH); 
    digitalWrite(MOTOR1_PIN2, LOW); 
    digitalWrite(MOTOR2_PIN1, HIGH); 
    digitalWrite(MOTOR2_PIN2, LOW); 
    Serial.println("Car moving forward"); 
  } else if (incomingData.button2 == 1) { 
    // Move backward 
    digitalWrite(MOTOR1_PIN1, LOW); 
    digitalWrite(MOTOR1_PIN2,HIGH); 
    digitalWrite(MOTOR2_PIN1, LOW); 
    digitalWrite(MOTOR2_PIN2, HIGH); 
    Serial.println("Car moving backward"); 
  } else if (incomingData.button3 == 1) { 
    // Turn left 
    digitalWrite(MOTOR1_PIN1, LOW); 
    digitalWrite(MOTOR1_PIN2, HIGH); 
    digitalWrite(MOTOR2_PIN1, HIGH); 
    digitalWrite(MOTOR2_PIN2, LOW); 
    Serial.println("Car turning left"); 
  } else if (incomingData.button4 == 1) { 
    // Turn right 
    digitalWrite(MOTOR1_PIN1, HIGH); 
    digitalWrite(MOTOR1_PIN2, LOW); 
    digitalWrite(MOTOR2_PIN1, LOW); 
    digitalWrite(MOTOR2_PIN2, HIGH); 
    Serial.println("Car turning right"); 
  } else { 
    stopCar(); // Stop the car if no buttons are pressed 
  } 
} 
 
// Function to control the robotic arm using joystick inputs 
void controlRoboticArm() { 
  // Map joystick values to servo angles with range limits 
  int baseAngle = constrain(map(incomingData.joystickX1, 0, 4095, BASE_MIN, BASE_MAX), BASE_MIN, BASE_MAX);
  int shoulderAngle = constrain(map(incomingData.joystickY1, 0, 4095, SHOULDER_MIN, SHOULDER_MAX), SHOULDER_MIN, SHOULDER_MAX);
  int elbowAngle = constrain(map(incomingData.joystickX2, 0, 4095, ELBOW_MIN, ELBOW_MAX), ELBOW_MIN, ELBOW_MAX);
  int wristAngle = constrain(map(incomingData.joystickY2, 0, 4095, WRIST_MIN, WRIST_MAX), WRIST_MIN, WRIST_MAX);
 
  baseServo.write(baseAngle); 
  shoulderServo.write(shoulderAngle); 
  elbowServo.write(elbowAngle); 
  wristServo.write(wristAngle); 
 
  Serial.println("Robotic arm controlled"); 
} 
 
// Function to stop the car 
void stopCar() { 
  digitalWrite(MOTOR1_PIN1, LOW); 
  digitalWrite(MOTOR1_PIN2, LOW); 
  digitalWrite(MOTOR2_PIN1, LOW); 
  digitalWrite(MOTOR2_PIN2, LOW); 
  Serial.println("Car stopped"); 
} 
 
// Function to reverse the car (used when the IR sensor detects a hole) 
void reverseCar() { 
  digitalWrite(MOTOR1_PIN1, LOW); 
  digitalWrite(MOTOR1_PIN2, HIGH); 
  digitalWrite(MOTOR2_PIN1, LOW); 
  digitalWrite(MOTOR2_PIN2, HIGH); 
  delay(500); // Reverse for 0.5 seconds 
  stopCar(); 
}
