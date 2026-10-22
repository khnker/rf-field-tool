#include "attack.h"
#include "radio.h"

static int attack_counter = 0;
static uint8_t attack_channel = 0;
static uint32_t last_attack_step_ms = 0;

void attack_init() {
    Serial.println(F("[ATTACK] Dual-Radio Constant Carrier Jammer initialized"));
}

void attack_run_step(int& counter) {
    uint32_t now = millis();
    if (now - last_attack_step_ms < 200) {
        return;
    }
    last_attack_step_ms = now;

    attack_counter++;
    counter = attack_counter;

    RF24& r1 = get_radio_1();
    RF24& r2 = get_radio_2();

    attack_channel = (attack_channel + 13) % (ATTACK_CHANNEL_MAX + 1);
    uint8_t channel2 = (attack_channel + 64) % (ATTACK_CHANNEL_MAX + 1);

    r1.setChannel(attack_channel);
    r2.setChannel(channel2);

    r1.startConstCarrier(RF24_PA_MAX, attack_channel);
    r2.startConstCarrier(RF24_PA_MAX, channel2);
}
