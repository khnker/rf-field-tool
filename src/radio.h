#ifndef RADIO_H
#define RADIO_H

#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>

// Radio 1 pins (CE, CSN)
#define R1_CE  4
#define R1_CSN 5

// Radio 2 pins (CE, CSN)
#define R2_CE  21
#define R2_CSN 22

void radios_init();
RF24& get_radio_1();
RF24& get_radio_2();

#endif
