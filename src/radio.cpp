#include "radio.h"

static RF24 radio1(R1_CE, R1_CSN);
static RF24 radio2(R2_CE, R2_CSN);
static bool radio1_ok = false;
static bool radio2_ok = false;

void radios_init() {
    // Shared SPI bus uses default VSPI pins on ESP32 (MOSI=23, MISO=19, SCK=18)
    SPI.begin();

    radio1_ok = radio1.begin();
    if (!radio1_ok) {
        Serial.println(F("Radio 1 init failed!"));
    } else {
        radio1.setAutoAck(false);
        radio1.startListening();
        Serial.println(F("Radio 1 initialized successfully."));
    }

    radio2_ok = radio2.begin();
    if (!radio2_ok) {
        Serial.println(F("Radio 2 init failed!"));
    } else {
        radio2.setAutoAck(false);
        radio2.startListening();
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

void radios_diagnostic() {
    Serial.println(F("=== RADIOS DIAGNOSTIC ==="));
    Serial.print(F("Radio 1 (CE=")); Serial.print(R1_CE);
    Serial.print(F(", CSN=")); Serial.print(R1_CSN);
    Serial.print(F(") OK: ")); Serial.println(radio1_ok ? "YES" : "NO");
    if (radio1_ok) {
        Serial.print(F("  Channel: ")); Serial.println(radio1.getChannel());
        Serial.print(F("  PA Level: ")); Serial.println(radio1.getPALevel());
        Serial.print(F("  DataRate: ")); Serial.println(radio1.getDataRate() == RF24_2MBPS ? "2Mbps" : (radio1.getDataRate() == RF24_1MBPS ? "1Mbps" : "250kbps"));
    }

    Serial.print(F("Radio 2 (CE=")); Serial.print(R2_CE);
    Serial.print(F(", CSN=")); Serial.print(R2_CSN);
    Serial.print(F(") OK: ")); Serial.println(radio2_ok ? "YES" : "NO");
    if (radio2_ok) {
        Serial.print(F("  Channel: ")); Serial.println(radio2.getChannel());
        Serial.print(F("  PA Level: ")); Serial.println(radio2.getPALevel());
        Serial.print(F("  DataRate: ")); Serial.println(radio2.getDataRate() == RF24_2MBPS ? "2Mbps" : (radio2.getDataRate() == RF24_1MBPS ? "1Mbps" : "250kbps"));
    }
    Serial.println(F("========================="));
}
