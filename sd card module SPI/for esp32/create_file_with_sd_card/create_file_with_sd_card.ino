#include <SPI.h>
#include <SD.h>

// SD card module pins
#define SD_CS_PIN 5 // Chip select pin
#define SD_SCK_PIN 18 // SCK pin
#define SD_MISO_PIN 19 // MISO pin
#define SD_MOSI_PIN 23 // MOSI pin

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // Wait for serial port to connect. Needed for native USB port only
  }

  Serial.print("Initializing SD card...");

  // Initialize SPI bus with custom pin definitions
  SPI.begin(SD_SCK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN);

  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card initialized successfully!");

  // Create a file named "test.txt" in the root directory of the SD card
  File dataFile = SD.open("/test.txt", FILE_WRITE);
  if (dataFile) {
    Serial.println("Writing to test.txt...");
    dataFile.println("Testing SD card.");
    dataFile.close();
    Serial.println("Done writing.");
  } else {
    Serial.println("Error opening /test.txt for writing.");
  }
}

void loop() {
  // Nothing to do here
}
