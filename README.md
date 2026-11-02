# ESP32 Flood & Fire Monitoring System with OLED Display

An ESP32-based environmental safety monitoring station that tracks ambient temperature, humidity, water level/flood presence, and fire/flame hazards in real-time. Data is displayed dynamically on a 0.96" I2C SSD1306 OLED screen and logged to the Serial Monitor.

---

## 📌 Features

- **Temperature & Humidity**: Measured using a DHT11 sensor (sampled every 2 seconds).
- **Flood / Water Detection**: Monitored via an analog water level/soil moisture sensor (12-bit ADC).
- **Fire / Flame Detection**: Dual monitoring using both analog flame intensity (`FLAME_AO`) and digital threshold trigger (`FLAME_DO`).
- **OLED Display Interface**: 128x64 graphical status display updated smoothly every 500ms.
- **Non-blocking Execution**: Timed events managed via `millis()` timers without blocking `delay()` calls in the main loop.
- **Serial Telemetry**: Real-time diagnostic stream at 115200 baud.

---

## 🛠️ Hardware Requirements

| Component | Quantity | Description |
| :--- | :--- | :--- |
| **ESP32 Dev Module** | 1 | Microcontroller board |
| **SSD1306 OLED Display** | 1 | 0.96" 128x64 I2C display (0x3C) |
| **DHT11 Sensor** | 1 | Temperature and humidity sensor |
| **Water Level Sensor** | 1 | Analog water/rain detection board |
| **Flame Sensor Module** | 1 | Infrared flame sensor (AO + DO pins) |
| **Jumper Wires & Breadboard** | - | Wiring connections |

---

## 🔌 Pin Mapping

| Peripheral | Sensor Pin | ESP32 GPIO | Description / Notes |
| :--- | :--- | :--- | :--- |
| **OLED Display** | SDA | `GPIO 25` | Custom I2C Data line |
| **OLED Display** | SCL | `GPIO 26` | Custom I2C Clock line |
| **DHT11** | DATA / OUT | `GPIO 27` | Digital sensor pin |
| **Water Sensor** | Analog SIG | `GPIO 34` | ADC1 Input only |
| **Flame Sensor** | AO (Analog) | `GPIO 33` | ADC1 Input |
| **Flame Sensor** | DO (Digital) | `GPIO 32` | Digital input (`INPUT_PULLUP`, Active LOW) |
| **Power** | VCC | `3.3V` / `5V` | Connect per module spec |
| **Ground** | GND | `GND` | Common ground for all sensors |

---

## 📚 Required Arduino Libraries

Ensure the following libraries are installed via the Arduino IDE Library Manager (**Sketch** > **Include Library** > **Manage Libraries...**):

1. **Adafruit SSD1306** (by Adafruit)
2. **Adafruit GFX Library** (by Adafruit)
3. **DHT sensor library** (by Adafruit)
4. **Adafruit Unified Sensor** (dependency for DHT)

---

## 🚀 Getting Started

### 1. Arduino IDE Configuration
1. Open the Arduino IDE.
2. Go to **Tools** > **Board** > **esp32** > select **ESP32 Dev Module** (or your specific board).
3. Connect your ESP32 to your computer using a USB cable.
4. Select the correct COM/Serial port under **Tools** > **Port**.
5. Set the upload speed (default `921600` or `115200`).

### 2. Upload the Code
1. Open [`esp_sensors_oled.ino`](esp_sensors_oled.ino).
2. Click the **Verify** (checkmark) button to compile.
3. Click the **Upload** (arrow) button to flash to the ESP32.
4. Open the **Serial Monitor** at **115200 baud** to view live logs.

---

## 🖥️ Serial Monitor Output Preview

```text
MONITORING SYSTEM STARTED
----- LIVE SENSOR DATA -----
Temperature: 26.40
Humidity: 58.00
Water ADC: 120
Flame Analog: 3840
Flame Digital: 1
Fire Status: SAFE
```

---

## 📄 License

This project is open-source and available under the [MIT License](LICENSE).

# esp-32-sensors-and-oled-test-code-
