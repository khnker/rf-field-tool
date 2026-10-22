#ifndef ATTACK_H
#define ATTACK_H

#include <Arduino.h>
#include "radio.h"

// nRF24 exposes channels 0..125 (126 channels total)
#define ATTACK_CHANNEL_MAX 125

// Minimum milliseconds between two attack steps.
// Without it the step rate is bounded only by the radio write time, the UI and
// the serial output saturate and the mode looks frozen on a single step.
#define ATTACK_STEP_INTERVAL_MS 100

void attack_init();
void attack_run_step(int& attack_counter);

#endif
