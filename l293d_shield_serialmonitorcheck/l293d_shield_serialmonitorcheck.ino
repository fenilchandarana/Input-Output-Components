#include "AFMotor_R4.h"

// Create motor objects for M1-M4
AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

const int MOTOR_SPEED = 100; // Fixed speed for all motors
const int RUN_TIME = 2000;   // 2 seconds

void setup() {
  Serial.begin(9600);
  Serial.println("Serial Motor Control Started");
  Serial.println("Commands: m1 cw | m1 ccw | m2 cw | m2 ccw | ... m4 cw/ccw");
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n'); // read the command
    cmd.trim();  // remove any spaces or newline chars

    if (cmd.length() >= 4) {
      char motorChar = cmd.charAt(1);       // motor number: '1'-'4'
      String dir = cmd.substring(3);        // direction: "cw" or "ccw"

      AF_DCMotor* selectedMotor = nullptr;

      switch (motorChar) {
        case '1': selectedMotor = &motor1; break;
        case '2': selectedMotor = &motor2; break;
        case '3': selectedMotor = &motor3; break;
        case '4': selectedMotor = &motor4; break;
        default: break;
      }

      if (selectedMotor != nullptr) {
        if (dir.equalsIgnoreCase("cw")) {
          selectedMotor->setSpeed(MOTOR_SPEED);
          selectedMotor->run(FORWARD);
        } else if (dir.equalsIgnoreCase("ccw")) {
          selectedMotor->setSpeed(MOTOR_SPEED);
          selectedMotor->run(BACKWARD);
        } else {
          Serial.println("Invalid direction! Use cw or ccw");
          return;
        }

        Serial.print("Running ");
        Serial.print(cmd);
        Serial.println(" for 2 seconds...");
        delay(RUN_TIME);

        selectedMotor->run(RELEASE);
        Serial.println("Motor stopped.");
      } else {
        Serial.println("Invalid motor! Use m1, m2, m3, or m4");
      }
    }
  }
}
