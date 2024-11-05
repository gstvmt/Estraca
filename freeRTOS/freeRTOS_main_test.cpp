#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "LoRa.hpp"
#include "imu.hpp"
#include "gps.hpp"

// Declaração das tasks
void taskLoRa(void *pvParameters);
void taskIMU(void *pvParameters);
void taskGPS(void *pvParameters);

void setup() {
  Serial.begin(115200);
  Serial2.begin(GPS_BAUDRATE, SERIAL_8N1, 16, 17);

  // Join the bus as Controller
  // Using the I2C communication at fast mode (400kHz)
  Wire.begin();
  Wire.setClock(400000);

  initializeLora(); // start LoRa
  powMan(); // Calling mpu power management function
  sep(60);

  gyroConfig(GYRO_CONFIG_MODE); // Select Mode 0: 250dps
  accConfig(ACC_CONFIG_MODE); // Select Mode 2: +-8g

  accData(true, ACC_CONFIG_MODE); // Calibration for Acceleration
  gyroData(true, GYRO_CONFIG_MODE); // Calibration for Gyroscope

  delay(1500);
  sep(60);

  // Create Tasks - Allow the system to decide which core to use
  xTaskCreate(taskLoRa, "Task LoRa", 4096, NULL, 2, NULL); // Higher priority
  xTaskCreate(taskIMU, "Task IMU", 4096, NULL, 1, NULL);   // Lower priority
  xTaskCreate(taskGPS, "Task GPS", 4096, NULL, 1, NULL);  //Lower priority

//   xTaskCreatePinnedToCore(taskLoRa, "Task LoRa", 4096, NULL, 2, NULL, 1); // Higher priority
//   xTaskCreatePinnedToCore(taskIMU, "Task IMU", 4096, NULL, 1, NULL, 1);   // Lower priority
//   xTaskCreatePinnedToCore(taskGPS, "Task GPS", 4096, NULL, 1, NULL, 1);   // Lower priority
}

void loop() {
  // Empty loop, due to freeRTOS
}

// Lora task - Higher priority
void taskLoRa(void *pvParameters) {
  while (true) {
    msgLoRa();
    sep(60);
    vTaskDelay(pdMS_TO_TICKS(1000)); // Delay time
  }
}

// IMU task - Lower priority
void taskIMU(void *pvParameters) {
  while (true) {
    accData(false, ACC_CONFIG_MODE);
    gyroData(false, GYRO_CONFIG_MODE);
    sep(60);
    vTaskDelay(pdMS_TO_TICKS(500)); // Delay time
  }
}

// GPS task - Lower priority
void taskGPS(void *pvParameters) {
  while (true) {
    readGPS();
    sep(60);
    vTaskDelay(pdMS_TO_TICKS(1000)); // Delay time
  }
}
