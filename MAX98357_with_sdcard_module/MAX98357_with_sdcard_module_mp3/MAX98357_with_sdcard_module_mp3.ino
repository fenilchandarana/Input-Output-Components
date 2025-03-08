#include "Arduino.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include "AudioFileSourceSD.h"
#include "AudioFileSourceID3.h"
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2S.h"

// SD Card Pins
#define SD_CS          5
#define SPI_MOSI      23 
#define SPI_MISO      19
#define SPI_SCK       18

// I2S Pins (MAX98357)
#define I2S_DOUT      22
#define I2S_BCLK      26
#define I2S_LRC       25

// Create audio objects
AudioGeneratorMP3 *mp3;
AudioFileSourceSD *file;
AudioOutputI2S *out;

void setup() {
    Serial.begin(115200);

    // Initialize SD Card
    if (!SD.begin(SD_CS)) {
        Serial.println("SD Card Mount Failed!");
        return;
    }
    Serial.println("SD Card Initialized.");

    // Setup I2S audio output
    out = new AudioOutputI2S();
    out->SetPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    out->SetGain(0.8); // Adjust volume (0.0 to 1.0)

    // Open MP3 file from SD card
    file = new AudioFileSourceSD("/test.mp3");
    mp3 = new AudioGeneratorMP3();
    mp3->begin(file, out);
}

void loop() {
    if (mp3->isRunning()) {
        if (!mp3->loop()) {
            Serial.println("Playback finished. Stopping.");
            mp3->stop();
            delete mp3;
            delete file;
            mp3 = NULL;
            file = NULL;
            delay(1000);
        }
    }
}
