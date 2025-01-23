#include "EEPROM.h"

void setup() {
  Serial.begin(9600);
  delay(1000);
  Serial.println("Testing EEPROMClass\n");
  
  // Instantiate EEPROM object
  EEPROMClass eeprom("eeprom");

  if (!eeprom.begin(0x1000)) { // Initialize EEPROM with starting address 0x1000
    Serial.println("Failed to initialise EEPROM");
    Serial.println("Restarting...");
    delay(1000);
    ESP.restart();
  }

  const char* hello = "hello world";
  char readBuffer[32];

  // Write "hello world" to EEPROM
  eeprom.writeString(0, hello);
  Serial.println("Data written to EEPROM successfully!");

  // Read from EEPROM
  eeprom.readString(0, readBuffer, sizeof(readBuffer));
  Serial.print("Data read from EEPROM: ");
  Serial.println(readBuffer);
}

void loop() {
  // Nothing to do here
}
