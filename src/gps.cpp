#include <Arduino.h>
#include "gps.hpp" 

void readGPS(){

  Serial.printf("%d GPS bytes available\n", Serial2.available());

  while(Serial2.available()){
    gps.encode(Serial2.read());
  }

  if (gps.location.isValid()) {

    Serial.print(F("Latitude: "));
    Serial.println(gps.location.lat(),6);

    Serial.print(F("Longitude: "));
    Serial.println(gps.location.lng(),6);

    Serial.print(F("Altitude: "));
    if (gps.altitude.isValid())
      Serial.println(gps.altitude.meters());
    else
      Serial.println(F("INVALID"));

  } else {
    Serial.println(F("Location: INVALID"));
  }

  Serial.print(F("Speed: "));
  if (gps.speed.isValid()) {
    Serial.print(gps.speed.kmph());
    Serial.println(F(" km/h"));
  } else {
    Serial.println(F("INVALID"));
  }

  Serial.print(F("GPS date&time: "));
  if (gps.date.isValid() && gps.time.isValid()) {
    Serial.print(gps.date.year());
    Serial.print(F("-"));
    Serial.print(gps.date.month());
    Serial.print(F("-"));
    Serial.print(gps.date.day());
    Serial.print(F(" "));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    Serial.println(gps.time.second());
  } else {
    Serial.println(F("INVALID"));
  }

  Serial.println();

  
  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
}