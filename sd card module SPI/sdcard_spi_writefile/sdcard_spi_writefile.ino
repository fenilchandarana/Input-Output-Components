#include <SPI.h>
#include <SD.h>

const int chipSelect = 2; // CS pin connected to pin 10 on Arduino

void setup() {
  Serial.begin(9600);
  
  // Initialize SD card
  if (!SD.begin(chipSelect)) {
    Serial.println("SD card initialization failed.");
    return;
  }
  Serial.println("SD card initialized.");
  
  // Create and open a new file
  File dataFile = SD.open("data.txt", FILE_WRITE);
  
  // Check if the file opened successfully
  if (dataFile) {
    Serial.println("Writing to file...");
    
    // Write data to the file
    dataFile.println("Hello, world!");
    
    // Close the file
    dataFile.close();
    
    Serial.println("File written successfully.");
  } else {
    Serial.println("Error opening file.");
  }
}

void loop() {
  // Nothing to do here
}
