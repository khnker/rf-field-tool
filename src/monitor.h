#ifndef MONITOR_H
#define MONITOR_H

#include <Arduino.h>
#include "radio.h"

void monitor_init();
void monitor_run_step(int& packets_seen);

#endif
