#include "ui.h"

static Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
static uint8_t anim_frame = 0;

void ui_init() {
    pinMode(PIN_BOOT, INPUT_PULLUP);
    Wire.begin(PIN_SDA, PIN_SCL);

    if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;);
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0,20);
    display.println(F("  RF FIELD TOOL  "));
    display.setCursor(0,35);
    display.println(F("   INITIALIZING..."));
    display.display();
    delay(1200);
}

void ui_update(const String& status, const String& mode, int rssi) {
    display.clearDisplay();
    anim_frame++;

    if (mode.indexOf("ATTACK") >= 0) {
        // Massive ATTACK text without status line
        display.setTextSize(3);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(4, 4);
        display.print(F("ATTACK"));

        // Blinking indicator box
        if ((anim_frame / 3) % 2 == 0) {
            display.fillRect(110, 8, 14, 14, SSD1306_WHITE);
        } else {
            display.drawRect(110, 8, 14, 14, SSD1306_WHITE);
        }

        display.drawLine(0, 32, 128, 32, SSD1306_WHITE);

        display.setTextSize(1);
        display.setCursor(0, 38);
        display.print(F("TX PACKETS:"));

        display.setTextSize(2);
        display.setCursor(0, 48);
        display.println(rssi);

        display.display();
        return;
    }

    // Standard UI for SCAN / MONITOR
    // Header bar
    display.fillRect(0, 0, 128, 12, SSD1306_WHITE);
    display.setTextColor(SSD1306_BLACK);
    display.setTextSize(1);
    display.setCursor(2, 2);
    display.print(mode);

    // Right side animated pulse / icon
    if ((anim_frame / 4) % 2 == 0) {
        display.fillCircle(120, 6, 3, SSD1306_BLACK);
    } else {
        display.drawCircle(120, 6, 3, SSD1306_BLACK);
    }

    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 18);
    display.print(F("Status: ")); display.println(status);

    display.setCursor(0, 30);
    display.print(F("Metric: ")); display.println(rssi);

    // Animated waveform / activity graph at the bottom
    for (int x = 0; x < 128; x += 4) {
        int h = (sin((x + anim_frame * 6) * 0.1) + 1.0) * 8.0;
        display.drawFastVLine(x, 58 - h, h, SSD1306_WHITE);
    }

    display.drawLine(0, 60, 128, 60, SSD1306_WHITE);
    display.display();
}

bool ui_is_boot_pressed() {
    return digitalRead(PIN_BOOT) == LOW;
}
