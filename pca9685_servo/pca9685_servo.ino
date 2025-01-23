// File: servo_control.ino

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// Create the PWM driver object
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SDA_PIN 21
#define SCL_PIN 22

// Define the min and max pulse lengths for servos
#define SERVOMIN  150 // Minimum pulse length count (out of 4096)
#define SERVOMAX  600 // Maximum pulse length count (out of 4096)

// Function to convert angle to pulse length
uint16_t angleToPulse(int angle) {
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

void setup() {
  // Initialize I2C communication
  Wire.begin(SDA_PIN, SCL_PIN);

  // Initialize the PCA9685
  pwm.begin();
  pwm.setPWMFreq(60); // Analog servos run at ~60 Hz

  Serial.begin(9600);

  // Debug print to indicate setup start
  Serial.println("Initializing servos to 0 degrees...");

  // Set the first four servos to 0 degrees at the start simultaneously
  for (uint8_t i = 0; i < 4; i++) {
    setServoAngle(i, 0);
  }

  // Add a delay to ensure all servos have time to move to 0 degrees
  delay(2000);

  // Debug print to indicate setup complete
  Serial.println("Initialization complete. All servos set to 0 degrees.");
}

void setServoAngle(uint8_t servoNum, uint8_t angle) {
  if (servoNum < 0 || servoNum > 15) {
    Serial.println("Invalid servo number!");
    return;
  }
  if (angle < 0 || angle > 20) {
    Serial.println("Invalid angle! Must be between 0 and 20 degrees.");
    return;
  }

  // Convert the angle to a pulse length
  uint16_t pulseLength = angleToPulse(angle);
  pwm.setPWM(servoNum, 0, pulseLength);

  // Debug prints for each servo setting
  Serial.print("Servo ");
  Serial.print(servoNum);
  Serial.print(" set to ");
  Serial.print(angle);
  Serial.print(" degrees (pulse length: ");
  Serial.print(pulseLength);
  Serial.println(")");
}

void loop() {
  // Rotate servos 0, 1, 2, and 3 to 20 degrees one by one
  Serial.println("Moving servo 0 to 20 degrees...");
  setServoAngle(0, 20);
  delay(1000); // Add delay to observe the movement

  Serial.println("Moving servo 1 to 20 degrees...");
  setServoAngle(1, 20);
  delay(1000); // Add delay to observe the movement

  Serial.println("Moving servo 2 to 20 degrees...");
  setServoAngle(2, 20);
  delay(1000); // Add delay to observe the movement

  Serial.println("Moving servo 3 to 20 degrees...");
  setServoAngle(3, 20);
  delay(1000); // Add delay to observe the movement

  // Stop further execution to avoid repetitive movements
  while (true) {
    // Keeping the microcontroller idle
  }
}
