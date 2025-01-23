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
  // Example: Light up LEDs across both registers in sequence
  for (int i = 0; i < 16; i++) {
    // Prepare a 16-bit number to light up LEDs across both shift registers
    uint16_t leds = (1 << i);  // Shift a single bit to the current position

    digitalWrite(latchPin, LOW);  // Begin shifting the data
    shiftOut(dataPin, clockPin, LSBFIRST, leds & 0xFF);  // Shift out the lower 8 bits for first register
    shiftOut(dataPin, clockPin, LSBFIRST, leds >> 8);    // Shift out the upper 8 bits for second register
    digitalWrite(latchPin, HIGH);  // Latch the data to the outputs

    delay(100);  // Wait for a moment
  }
}
