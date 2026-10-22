#include "radio.h"

static RF24 radio1(R1_CE, R1_CSN);
static RF24 radio2(R2_CE, R2_CSN);

void radios_init() {
    // Shared SPI bus uses default VSPI pins on ESP32 (MOSI=23, MISO=19, SCK=18)
    SPI.begin();

    if (!radio1.begin()) {
        Serial.println(F("Radio 1 init failed!"));
    } else {
        radio1.setAutoAck(false);
        radio1.startListening();
    }

    if (!radio2.begin()) {
        Serial.println(F("Radio 2 init failed!"));
    } else {
        radio2.setAutoAck(false);
        radio2.startListening();
    }
}

RF24& get_radio_1() {
    return radio1;
}

RF24& get_radio_2() {
    return radio2;
}
