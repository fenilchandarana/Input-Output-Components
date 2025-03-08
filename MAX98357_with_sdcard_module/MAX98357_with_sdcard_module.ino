#include "Arduino.h"
#include "FS.h"
#include "SD.h"
#include "driver/i2s.h"

// SD Card Pins
#define SD_CS          5
#define SPI_MOSI      23 
#define SPI_MISO      19
#define SPI_SCK       18

// I2S Pins (MAX98357)
#define I2S_DOUT      22
#define I2S_BCLK      26
#define I2S_LRC       25

// I2S Configuration
#define I2S_NUM       I2S_NUM_0
#define SAMPLE_RATE   44100  // WAV file sample rate
#define BUFFER_SIZE   1024   // Buffer size for reading WAV data

// WAV File Path (Change this to match your SD card file)
const char* wavFilePath = "/test.wav"; 

void setup() {
    Serial.begin(115200);
    
    // Initialize SD Card
    if (!SD.begin(SD_CS)) {
        Serial.println("SD Card Mount Failed!");
        return;
    }
    Serial.println("SD Card Initialized.");

    // Initialize I2S
    i2s_config_t i2s_config = {
        .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX),
        .sample_rate = SAMPLE_RATE,
        .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
        .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
        .communication_format = I2S_COMM_FORMAT_STAND_I2S,
        .intr_alloc_flags = 0,
        .dma_buf_count = 8,
        .dma_buf_len = BUFFER_SIZE,
        .use_apll = false
    };

    i2s_pin_config_t pin_config = {
        .bck_io_num = I2S_BCLK,
        .ws_io_num = I2S_LRC,
        .data_out_num = I2S_DOUT,
        .data_in_num = I2S_PIN_NO_CHANGE
    };

    i2s_driver_install(I2S_NUM, &i2s_config, 0, NULL);
    i2s_set_pin(I2S_NUM, &pin_config);
    
    Serial.println("I2S Initialized.");
    
    // Play WAV file from SD card
    playWAV(wavFilePath);
}

void loop() {
    playWAV("/test.wav");  // Play the WAV file
    delay(1000);  // Wait 1 second before playing again
}


// Function to Play WAV File
void playWAV(const char* filename) {
    File file = SD.open(filename);
    if (!file) {
        Serial.println("Failed to open WAV file!");
        return;
    }

    // Reset I2S before playback
    i2s_stop(I2S_NUM);
    i2s_zero_dma_buffer(I2S_NUM);
    i2s_start(I2S_NUM);

    // Skip WAV Header (first 44 bytes)
    file.seek(44);

    uint8_t buffer[BUFFER_SIZE];
    uint8_t processedBuffer[BUFFER_SIZE];  // Separate buffer to avoid corruption
    size_t bytesRead;
    
    float volume = 1; // Set volume (0.0 = mute, 1.0 = max)
    
    Serial.println("Playing WAV File...");

    while ((bytesRead = file.read(buffer, sizeof(buffer))) > 0) {
        // Copy data to avoid modifying the original buffer
        memcpy(processedBuffer, buffer, bytesRead);

        // Adjust volume by modifying PCM values
        for (size_t i = 0; i < bytesRead; i += 2) {  
            int16_t sample = processedBuffer[i] | (processedBuffer[i + 1] << 8); // Convert 16-bit sample
            sample = sample * volume;  // Apply volume scaling
            
            // Prevent overflow/clipping
            if (sample > 32767) sample = 32767;
            if (sample < -32768) sample = -32768;

            processedBuffer[i] = sample & 0xFF;  
            processedBuffer[i + 1] = (sample >> 8) & 0xFF;
        }

        size_t bytes_written;
        i2s_write(I2S_NUM, processedBuffer, bytesRead, &bytes_written, portMAX_DELAY);
    }

    Serial.println("Playback finished.");
    file.close();

    // Ensure clean playback next time
    i2s_stop(I2S_NUM);
    i2s_zero_dma_buffer(I2S_NUM);
}
