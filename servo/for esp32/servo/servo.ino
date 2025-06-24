#include <ESP32Servo.h>

Servo myServo;  // Create a servo object
int servoPin = 18; // GPIO pin connected to the servo

void setup() {
  Serial.begin(9600);
//  myServo.setPeriodHertz(50);    // Standard 50 hz servo
  myServo.attach(servoPin);      // Attach the servo to a pin
}

void loop() {
  myServo.write(0);   // Move servo to 0 degrees
  delay(1000);
  myServo.write(20);  // Move servo to 90 degrees
  delay(1000);
  myServo.write(0); // Move servo to 180 degrees
  delay(1000);
}
