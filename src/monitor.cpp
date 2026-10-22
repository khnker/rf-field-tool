#include "monitor.h"

void monitor_init() {
    RF24& r2 = get_radio_2();
    r2.setChannel(76);
    r2.openReadingPipe(1, 0xF0F0F0F0E1LL);
    r2.startListening();
}

void monitor_run_step(int& packets_seen) {
    RF24& r2 = get_radio_2();
    static int count = 0;
    if (r2.available()) {
        count++;
        char buf[32];
        r2.read(&buf, sizeof(buf));
    }
    packets_seen = count;
}
