#include "radio.h"

static RF24 radio1(R1_CE, R1_CSN);
static RF24 radio2(R2_CE, R2_CSN);
static bool radio1_ok = false;
static bool radio2_ok = false;

void radios_init() {
    // Initialize standard VSPI bus
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);

    radio1_ok = false;
    radio2_ok = false;

    if (!radio1.begin()) {
        Serial.println(F("Radio 1 init failed! Check CE(4)/CSN(5) wiring."));
    } else {
        radio1.setAutoAck(false);
        radio1.setRetries(0, 0);
        radio1.setPALevel(RF24_PA_MAX);
        radio1.setDataRate(RF24_2MBPS);
        radio1_ok = true;
        Serial.println(F("Radio 1 initialized successfully."));
    }

    if (!radio2.begin()) {
        Serial.println(F("Radio 2 init failed! Check CE(16)/CSN(17) wiring."));
    } else {
        radio2.setAutoAck(false);
        radio2.setRetries(0, 0);
        radio2.setPALevel(RF24_PA_MAX);
        radio2.setDataRate(RF24_2MBPS);
        radio2_ok = true;
        Serial.println(F("Radio 2 initialized successfully."));
    }
}

RF24& get_radio_1() {
    return radio1;
}

RF24& get_radio_2() {
    return radio2;
}

bool radios_ready() {
    return radio1_ok && radio2_ok;
}
