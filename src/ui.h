#ifndef UI_H
#define UI_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C

// Pin definitions as requested
#define PIN_SDA 32
#define PIN_SCL 33
#define PIN_BOOT 0

void ui_init();
void ui_update(const String& status, const String& mode, int rssi);
bool ui_is_boot_pressed();

#endif
