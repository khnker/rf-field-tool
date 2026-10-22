#ifndef RADIO_H
#define RADIO_H

#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>

// Standard VSPI pins on ESP32
#define SPI_SCK  18
#define SPI_MISO 19
#define SPI_MOSI 23

// Radio 1 (Left module)
#define R1_CE    4
#define R1_CSN   5

// Radio 2 (Right/Second module)
#define R2_CE    16
#define R2_CSN   17

void radios_init();
RF24& get_radio_1();
RF24& get_radio_2();

// True only when both radios answered begin()
bool radios_ready();

#endif
