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

  // Open the file for reading
  File dataFile = SD.open("text.txt");
  
  // Check if the file opened successfully
  if (dataFile) {
    Serial.println("Contents of text.txt:");

    // Read from the file until there's nothing else to read
    while (dataFile.available()) {
      Serial.write(dataFile.read());
    }
    
    // Close the file
    dataFile.close();
  } else {
    Serial.println("Error opening file.");
  }
}

void loop() {
  // Nothing to do here
}
