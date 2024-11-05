#ifndef lora_hpp
#define lora_hpp

#include <SPI.h>              // include libraries
#include <LoRa.h>

const int csPin = 7;          // LoRa radio chip select
const int resetPin = 6;       // LoRa radio reset
const int irqPin = 1;         // change for your board; must be a hardware interrupt pin
const int interval = 2000;          // interval between sends

String outgoing;              // outgoing message

byte msgCount = 0;            // count of outgoing messages
byte localAddress = 0xBB;     // address of this device
byte destination = 0xFF;      // destination to send to
long lastSendTime = 0;        // last send time


void sendMessage(String outgoing);
void onReceive(int packetSize);
void initializeLora();
void msgLoRa();

#endif