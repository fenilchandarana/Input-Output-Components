#include <Wire.h>

#define MPU6050_ADDR 0x68  // I2C address of MPU6050

void setup() {
    Serial.begin(115200);
    Wire.begin(21, 22); // SDA -> GPIO21, SCL -> GPIO22

    // Wake up MPU6050 (it starts in sleep mode)
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x6B);  // PWR_MGMT_1 register
    Wire.write(0);     // Set to 0 to wake up the sensor
    Wire.endTransmission();
    
    Serial.println("MPU6050 initialized successfully!");
}

void loop() {
    int16_t accelX, accelY, accelZ;
    int16_t gyroX, gyroY, gyroZ;

    // Read accelerometer data
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x3B);  // Starting register for accelerometer
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050_ADDR, 6, true); // Request 6 bytes
    accelX = (Wire.read() << 8) | Wire.read();
    accelY = (Wire.read() << 8) | Wire.read();
    accelZ = (Wire.read() << 8) | Wire.read();

    // Read gyroscope data
    Wire.beginTransmission(MPU6050_ADDR);
    Wire.write(0x43);  // Starting register for gyroscope
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050_ADDR, 6, true); // Request 6 bytes
    gyroX = (Wire.read() << 8) | Wire.read();
    gyroY = (Wire.read() << 8) | Wire.read();
    gyroZ = (Wire.read() << 8) | Wire.read();

    // Print values
    Serial.print("Accel X: "); Serial.print(accelX);
    Serial.print(" | Accel Y: "); Serial.print(accelY);
    Serial.print(" | Accel Z: "); Serial.println(accelZ);

    Serial.print("Gyro X: "); Serial.print(gyroX);
    Serial.print(" | Gyro Y: "); Serial.print(gyroY);
    Serial.print(" | Gyro Z: "); Serial.println(gyroZ);

    Serial.println("----------------------");
    delay(500);
}
