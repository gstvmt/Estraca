#ifndef gps_hpp
#define gps_hpp

#include <TinyGPS++.h>

#define GPS_BAUDRATE 9600
TinyGPSPlus gps; //TinyGPS object

void readGPS(); // gps reading function

#endif