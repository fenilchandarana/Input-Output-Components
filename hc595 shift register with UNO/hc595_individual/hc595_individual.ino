int latchPin = 11;   // RCLK pin of 74HC595
int clockPin = 13;   // SRCLK pin of 74HC595
int dataPin = 10;    // SER pin of 74HC595

void setup() {
  // Set the pins as output
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  // Define the LED positions for both registers
  uint16_t ledsOff = 0b0000000000000000; // All LEDs off
  uint16_t ledsOn = 0b1000100000000000;  // 10th LED (2nd LED of the 2nd register) on

  // Blink the 10th LED (2nd LED of 2nd register)
  digitalWrite(latchPin, LOW);  // Begin shifting the data
  shiftOut(dataPin, clockPin, LSBFIRST, ledsOff & 0xFF);  // Shift out the lower 8 bits for first register
  shiftOut(dataPin, clockPin, LSBFIRST, ledsOff >> 8);    // Shift out the upper 8 bits for second register
  digitalWrite(latchPin, HIGH);  // Latch the data to the outputs
  delay(1000);  // Wait for 1 second
  
  digitalWrite(latchPin, LOW);  // Begin shifting the data
  shiftOut(dataPin, clockPin, LSBFIRST, ledsOn & 0xFF);  // Shift out the lower 8 bits for first register
  shiftOut(dataPin, clockPin, LSBFIRST, ledsOn >> 8);    // Shift out the upper 8 bits for second register
  digitalWrite(latchPin, HIGH);  // Latch the data to the outputs
  delay(1000);  // Wait for 1 second
}
