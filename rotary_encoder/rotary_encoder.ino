/*
  Rotary Encoder and Button Demo
  Demonstrates operation of Rotary Encoder and a Button
  Displays results on Serial Monitor
  DroneBot Workshop 2019
  https://dronebotworkshop.com
  LEDs removed for simplicity
*/

// Rotary Encoder Inputs
#define inputCLK 25
#define inputDT 26

// Button Input
#define inputButton 27

int counter = 0; 
int currentStateCLK;
int previousStateCLK;
int buttonState;
int lastButtonState = HIGH; // the previous state of the button

unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

String encdir = "";

void setup() { 
  // Set encoder pins as inputs  
  pinMode(inputCLK, INPUT);
  pinMode(inputDT, INPUT);
  
  // Set button pin as input with internal pull-up resistor
  pinMode(inputButton, INPUT_PULLUP);

  // Setup Serial Monitor
  Serial.begin(9600);
   
  // Read the initial state of inputCLK
  previousStateCLK = digitalRead(inputCLK);
} 

void loop() { 
  // Read the current state of inputCLK
  currentStateCLK = digitalRead(inputCLK);
  
  // Read the state of the button
  int reading = digitalRead(inputButton);
  
  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }
  
  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      
      // only log the button press if the new button state is LOW
      if (buttonState == LOW) {
        Serial.println("Button Pressed");
      }
    }
  }

  // save the reading.  Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
  
  // If the previous and the current state of inputCLK are different then a pulse has occurred
  if (currentStateCLK != previousStateCLK) { 
    if (digitalRead(inputDT) == currentStateCLK) { // Encoder is rotating clockwise
      counter--;
      encdir = "CCW";
    } else { // Encoder is rotating counterclockwise
      counter++;
      encdir = "CW";
    }

    Serial.print("Direction: ");
    Serial.print(encdir);
    Serial.print(" -- Value: ");
    Serial.println(counter);
  } 
  // Update previousStateCLK with the current state
  previousStateCLK = currentStateCLK; 
}
