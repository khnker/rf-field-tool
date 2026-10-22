#ifndef SCAN_H
#define SCAN_H

#include <Arduino.h>
#include "radio.h"

void scan_init();
void scan_run_step(int& active_channel, int& max_rssi);

#endif
