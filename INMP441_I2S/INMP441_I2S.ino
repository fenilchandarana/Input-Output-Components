// Include I2S driver
#include "driver/i2s.h"

// Define I2S connections to INMP441
#define I2S_WS 25   // Word Select (LRCL)
#define I2S_SD 32   // Serial Data (DOUT)
#define I2S_SCK 33  // Serial Clock (BCLK)

// Use I2S Processor 0
#define I2S_PORT I2S_NUM_0

// Define buffer length
#define BUFFER_SIZE 1024
int16_t audioBuffer[BUFFER_SIZE];

void setup() {
  // Set up Serial Monitor
  Serial.begin(9600);
  Serial.println("Initializing I2S...");

  // Configure I2S
  const i2s_config_t i2s_config = {
    .mode = i2s_mode_t(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = 16000,                     // Sample rate: 16 kHz
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = I2S_COMM_FORMAT_I2S,
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1, // Interrupt level
    .dma_buf_count = 8,
    .dma_buf_len = BUFFER_SIZE,
    .use_apll = false
  };

  const i2s_pin_config_t pin_config = {
    .bck_io_num = I2S_SCK,   // BCLK
    .ws_io_num = I2S_WS,     // LRCL
    .data_out_num = I2S_PIN_NO_CHANGE,
    .data_in_num = I2S_SD    // DOUT
  };

  // Install and start I2S
  i2s_driver_install(I2S_PORT, &i2s_config, 0, NULL);
  i2s_set_pin(I2S_PORT, &pin_config);
  i2s_start(I2S_PORT);

  Serial.println("I2S initialized. Start making noise!");
}

void loop() {
  size_t bytesRead = 0;

  // Read data from the microphone into the buffer
  esp_err_t result = i2s_read(I2S_PORT, &audioBuffer, BUFFER_SIZE * sizeof(int16_t), &bytesRead, portMAX_DELAY);

  if (result == ESP_OK) {
    int samplesRead = bytesRead / sizeof(int16_t);
    long sum = 0;

    // Calculate the average amplitude
    for (int i = 0; i < samplesRead; i++) {
      sum += abs(audioBuffer[i]);  // Use absolute value for intensity
    }

    int averageAmplitude = sum / samplesRead;

    // Print average amplitude to Serial Monitor
    Serial.print("Sound Intensity: ");
    Serial.println(averageAmplitude);

    // Simple noise detection
    if (averageAmplitude > 2000) { // Adjust threshold for your environment
      Serial.println("Loud noise detected!");
    }
  }
}
