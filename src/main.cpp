#include <Arduino.h>
#include "LoRa.hpp"
#include "imu.hpp"
#include "gps.hpp"


void setup() {

  Serial.begin(115200);
  Serial2.begin(GPS_BAUDRATE, SERIAL_8N1, 16, 17);

  // Join the bus as Controller
  // Using the I2C communication at fast mode (400kHz)
  Wire.begin();
  Wire.setClock(400000);
  
  initializeLora(); //start LoRa

  powMan(); // Calling mpu power management function
  sep(60);

 
  gyroConfig(GYRO_CONFIG_MODE); // Select Mode 0: 250dps
  accConfig(ACC_CONFIG_MODE); // Select Mode 2: +-8g

  
  accData(true, ACC_CONFIG_MODE); // Calibration for Acceleration
  gyroData(true, GYRO_CONFIG_MODE); // Calibration for Gyroscope

  delay(1500);
  sep(60);
}

void loop() {

  msgLoRa();

  sep(60);

  accData(false, ACC_CONFIG_MODE);
  gyroData(false, GYRO_CONFIG_MODE);

  sep(60);

  readGPS();

  sep(60);
  delay(300);
}

