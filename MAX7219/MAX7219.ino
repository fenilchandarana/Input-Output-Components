#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Define hardware type and pins
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 1
#define CS_PIN 12

// Create MD_MAX72XX instance directly (no scrolling text needed)
MD_MAX72XX mx = MD_MAX72XX(HARDWARE_TYPE, CS_PIN, MAX_DEVICES);

void setup() {
  mx.begin();
  mx.control(MD_MAX72XX::INTENSITY, 5);
  mx.clear();

  // Draw top and bottom rows
  for (uint8_t col = 0; col < 8; col++) {
    mx.setPoint(0, col, true);  // Top row
    mx.setPoint(7, col, true);  // Bottom row
  }

  // Draw left and right columns
  for (uint8_t row = 1; row < 7; row++) {
    mx.setPoint(row, 0, true);  // Left column
    mx.setPoint(row, 7, true);  // Right column
  }
}

void loop() {
  // Nothing to do in loop for static border
}
