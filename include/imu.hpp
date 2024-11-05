#ifndef imu_hpp
#define imu_hpp

#include <Wire.h>

// 0: 250 dps (131 LSB/dps); 1: 500 dps (65.5 LSB/dps) ; 2: 1000 dps ( 32.8 LSB/dps) ; 3: 2000 dps (16.4 LSB/dps)
#define GYRO_CONFIG_MODE 0

// 0: 2g (16384 LSB/g); 1: 4g (8192 LSB/g) ; 2: 8g (4096 LSB/g) ; 3: 16g (2048 LSB/g)
#define ACC_CONFIG_MODE 1

#define MPU_POWER_REGISTER 0x6B
#define MPU_MODE 0x6C
#define GYRO_MODE 0x1A
#define GYRO_CONFIG 0x1B
#define ACCEL_INIT 0x1C
#define ACCEL_CONFIG 0x1D
#define accX_H 0x3B
#define accY_H 0x3D
#define accZ_H 0x3F
#define gyroX_H 0x43
#define gyroY_H 0x45
#define gyroZ_H 0x47



void i2cWrite(uint8_t address, uint8_t reg, uint8_t val);
int16_t i2cRead(uint8_t address, int8_t reg);
void sep(int a);
void printAcc(bool status);
void printGyro(bool status);
void powMan();
void gyroConfig(uint8_t choice);
void accConfig(uint8_t choice);
void accData(bool status, int choice);
void gyroData(bool status, int choice);


#endif