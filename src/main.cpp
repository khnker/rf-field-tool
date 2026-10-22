#include <Arduino.h>
#include "ui.h"
#include "radio.h"
#include "scan.h"
#include "monitor.h"
#include "attack.h"

enum ToolMode {
    MODE_SCAN,
    MODE_MONITOR,
    MODE_ATTACK
};

static ToolMode current_mode = MODE_SCAN;

void setup() {
    Serial.begin(115200);
    delay(500);

    ui_init();
    radios_init();

    scan_init();
    monitor_init();
    attack_init();

    Serial.println(F("RF Field Tool MVP Initialized."));
}

void loop() {
    // Check BOOT button press to cycle modes
    if (ui_is_boot_pressed()) {
        delay(200); // debounce
        if (current_mode == MODE_SCAN) current_mode = MODE_MONITOR;
        else if (current_mode == MODE_MONITOR) current_mode = MODE_ATTACK;
        else current_mode = MODE_SCAN;
        while(ui_is_boot_pressed()); // wait release
    }

    int metric = 0;
    String mode_str = "";

    switch (current_mode) {
        case MODE_SCAN: {
            int ch = 0, rssi = 0;
            scan_run_step(ch, rssi);
            metric = ch;
            mode_str = "SCAN (Ch: " + String(ch) + ")";
            break;
        }
        case MODE_MONITOR: {
            int pkts = 0;
            monitor_run_step(pkts);
            metric = pkts;
            mode_str = "MONITOR";
            break;
        }
        case MODE_ATTACK: {
            int ac = 0;
            attack_run_step(ac);
            metric = ac;
            mode_str = "ATTACK (Stub)";
            break;
        }
    }

    ui_update("Running", mode_str, metric);
    delay(100);
}
