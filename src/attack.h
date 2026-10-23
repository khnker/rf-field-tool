#ifndef ATTACK_H
#define ATTACK_H

#include <Arduino.h>
#include "radio.h"

// nRF24 exposes channels 0..125 (126 channels total)
#define ATTACK_CHANNEL_MAX 125

// Zero delay for maximum transmission rate / fast hopping against FHSS (Bluetooth/BLE)
#define ATTACK_STEP_INTERVAL_MS 0

void attack_init();
void attack_run_step(int& attack_counter);

#endif
