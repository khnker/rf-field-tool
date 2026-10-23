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

static ToolMode current_mode = MODE_ATTACK;

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
    // Check Serial input for remote commands.
    static String cmd;
    static uint32_t cmd_last_byte_ms = 0;
    static bool cmd_pending = false;
    bool cmd_terminated = false;

    while (Serial.available() > 0) {
        char ch = (char)Serial.read();
        cmd_last_byte_ms = millis();
        if (ch == '\n' || ch == '\r') {
            cmd_terminated = true;
            break;
        }
        if (cmd.length() < 32) {
            cmd += ch;
            cmd_pending = true;
        }
    }

    if (cmd_pending && (cmd_terminated || (uint32_t)(millis() - cmd_last_byte_ms) > 200)) {
        cmd.trim();
        cmd.toLowerCase();
        if (cmd == "scan") {
            current_mode = MODE_SCAN;
            Serial.println(F("[CMD] Switched to SCAN mode"));
        } else if (cmd == "monitor") {
            current_mode = MODE_MONITOR;
            Serial.println(F("[CMD] Switched to MONITOR mode"));
        } else if (cmd == "attack") {
            current_mode = MODE_ATTACK;
            Serial.println(F("[CMD] Switched to ATTACK mode"));
        } else if (cmd == "status") {
            Serial.print(F("[STATUS] Current mode: "));
            if (current_mode == MODE_SCAN) Serial.println("SCAN");
            else if (current_mode == MODE_MONITOR) Serial.println("MONITOR");
            else Serial.println("ATTACK");
        } else if (cmd == "diags" || cmd == "diag") {
            radios_diagnostic();
        } else if (cmd == "help") {
            Serial.println(F("Available commands: scan, monitor, attack, status, diags, help"));
        } else if (cmd.length() > 0) {
            Serial.print(F("[CMD] Unknown command: "));
            Serial.println(cmd);
        }
        cmd = "";
        cmd_pending = false;
    }

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
            mode_str = "ATTACK (BT Jam)";
            break;
        }
    }

    ui_update("Running", mode_str, metric);

    // Remove delay in attack mode for maximum frequency-hopping speed
    if (current_mode != MODE_ATTACK) {
        delay(100);
    }
}
