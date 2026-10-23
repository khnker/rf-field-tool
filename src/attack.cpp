#include "attack.h"
#include "radio.h"

static int attack_counter = 0;

void attack_init() {
    Serial.println(F("[ATTACK] MAXIMUM AGGRESSION DUAL-RADIO JAMMER INITIALIZED"));
}

void attack_run_step(int& counter) {
    if (!radios_ready()) {
        return;
    }

    RF24& r1 = get_radio_1();
    RF24& r2 = get_radio_2();

    // Aggressive unrolled multi-channel hopping & carrier flooding
    for (int i = 0; i < 25; i++) {
        attack_counter++;
        uint8_t ch1 = (uint8_t)(attack_counter % 79);
        uint8_t ch2 = (uint8_t)((attack_counter * 37) % 79);

        r1.setChannel(ch1);
        r2.setChannel(ch2);

        r1.startConstCarrier(RF24_PA_MAX, ch1);
        r2.startConstCarrier(RF24_PA_MAX, ch2);
    }
    counter = attack_counter;
}
