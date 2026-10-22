#ifndef ATTACK_H
#define ATTACK_H

#include <Arduino.h>
#include "radio.h"

void attack_init();
void attack_run_step(int& attack_counter);

#endif
