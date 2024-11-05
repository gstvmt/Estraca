#ifndef lora_hpp
#define lora_hpp

#include <SPI.h>              // include libraries
#include <LoRa.h>


void sendMessage(String outgoing);
void onReceive(int packetSize);
void initializeLora();
void msgLoRa();

#endif