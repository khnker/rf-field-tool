# RF Field Tool (ESP32 + Dual NRF24L01+ + OLED)

Designed specifically for **ESP32 DevKitC V1.2** paired with **Dual NRF24L01+ PA/LNA** modules and an **0.96" I2C OLED Display (SSD1306)**. This firmware provides multi-mode RF analysis, packet monitoring, and high-speed frequency-hopping constant-carrier jamming (optimized for Bluetooth Classic audio disruption).

---

## Hardware Pinout Configuration (ESP32 DevKitC V1.2)

### SPI Bus (Shared)
- **SCK**: GPIO 18
- **MISO**: GPIO 19
- **MOSI**: GPIO 23

### Radio 1 (Left Module)
- **CE**: GPIO 4
- **CSN**: GPIO 5

### Radio 2 (Right Module)
- **CE**: GPIO 21
- **CSN**: GPIO 22

### OLED Display (I2C)
- **SDA**: GPIO 32
- **SCL**: GPIO 33
- **Address**: `0x3C`

### Controls
- **BOOT Button**: GPIO 0 (Short press to cycle modes: Scan -> Monitor -> Attack)

---

## Serial Commands & Diagnostics

Connect via serial monitor at **115200 baud**:
- `scan`: Switch to Channel Scan mode.
- `monitor`: Switch to Packet Monitor mode.
- `attack`: Switch to Ultra-High-Speed Bluetooth Classic Audio Jammer mode.
- `status`: Show current operating mode.
- `diags` / `diag`: Run hardware initialization diagnostics for both NRF24L01+ radios.
- `help`: List available commands.

---

## Build & Flash (PlatformIO)

```bash
# Compile firmware
python3 -m platformio run

# Flash to ESP32 (e.g. /dev/ttyUSB0)
python3 -m platformio run -t upload --upload-port /dev/ttyUSB0
```
