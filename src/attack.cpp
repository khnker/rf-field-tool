#include "attack.h"
#include "radio.h"

static int attack_counter = 0;
static uint8_t attack_channel = 0;
static uint32_t last_attack_step_ms = 0;

void attack_init() {
    Serial.println(F("[ATTACK] Dual-Radio Packet Jammer initialized"));
}

void attack_run_step(int& counter) {
    uint32_t now = millis();
    if (now - last_attack_step_ms < ATTACK_STEP_INTERVAL_MS) {
        return;
    }
    last_attack_step_ms = now;

    attack_counter++;
    counter = attack_counter;

    RF24& r1 = get_radio_1();
    RF24& r2 = get_radio_2();

    attack_channel = (attack_channel + 1) % 80;
    uint8_t channel2 = (attack_channel + 40) % 80;

    r1.setChannel(attack_channel);
    r2.setChannel(channel2);

    uint8_t payload[32] = {0xAA, 0x55, 0xAA, 0x55, 0x01, 0x02, 0x03, 0x04};

    r1.writeFast(payload, sizeof(payload));
    r2.writeFast(payload, sizeof(payload));
}
