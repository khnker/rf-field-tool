#include "scan.h"

static uint8_t current_channel = 0;

void scan_init() {
    RF24& r1 = get_radio_1();
    r1.setChannel(current_channel);
    r1.startListening();
}

void scan_run_step(int& active_channel, int& max_rssi) {
    RF24& r1 = get_radio_1();
    
    // Sweep channels 0 to 125
    current_channel = (current_channel + 1) % 126;
    r1.setChannel(current_channel);
    
    // Check carrier detect or test RSSI
    bool carrier = r1.testCarrier();
    active_channel = current_channel;
    max_rssi = carrier ? 1 : 0;
}
