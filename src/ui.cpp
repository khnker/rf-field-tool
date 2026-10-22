#include "ui.h"

static Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

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
    display.setCursor(0,0);
    display.println(F("RF Field Tool MVP"));
    display.display();
    delay(1000);
}

void ui_update(const String& status, const String& mode, int rssi) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print(F("Mode: ")); display.println(mode);
    display.setCursor(0, 16);
    display.print(F("Status: ")); display.println(status);
    display.setCursor(0, 32);
    display.print(F("RSSI/Val: ")); display.println(rssi);
    
    // Draw simple footer
    display.drawLine(0, 50, 128, 50, SSD1306_WHITE);
    display.setCursor(0, 54);
    display.print(F("BOOT: Switch Mode"));
    
    display.display();
}

bool ui_is_boot_pressed() {
    return digitalRead(PIN_BOOT) == LOW;
}
