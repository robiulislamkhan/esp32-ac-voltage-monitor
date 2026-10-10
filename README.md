# ESP32 AC Voltage Monitor with OLED Display

An ESP32-based AC voltage monitoring system using the **ZMPT101B AC voltage sensor** and a **128×64 SPI OLED display**. The project measures AC RMS voltage and displays the voltage reading and its status in real time.

## Features

- Real-time AC voltage measurement
- ZMPT101B voltage sensor integration
- ESP32 microcontroller
- 128×64 SPI OLED display
- Centered voltage reading, such as `AC Volt = 220V`
- Automatic voltage status detection
- Serial Monitor output for debugging
- Adjustable sensor sensitivity and calibration factor

## Hardware Requirements

- ESP32 development board
- ZMPT101B AC voltage sensor module
- 128×64 SPI OLED display
- Jumper wires
- Suitable insulated and enclosed AC test connections

## Hardware Connections

### OLED Display to ESP32

The pin configuration below assumes an SSD1306-compatible SPI OLED.

| OLED Pin | ESP32 Pin |
|---|---|
| VCC | 3.3V, if supported by the module |
| GND | GND |
| SCK / CLK | GPIO 18 |
| MOSI / SDA / DIN | GPIO 23 |
| CS | GPIO 5 |
| DC / A0 | GPIO 16 |
| RES / RST | GPIO 17 |

### ZMPT101B Sensor to ESP32

| ZMPT101B Pin | ESP32 Pin |
|---|---|
| OUT / S | GPIO 27 |
| GND | GND |
| VCC | Supply voltage supported by the sensor module |

**Important:** Verify the OLED controller and pin labels on your actual module before connecting it. ESP32 GPIOs are not 5V tolerant. Ensure the ZMPT101B output signal stays within the ESP32's permitted input range.

## Required Arduino Libraries

Install these libraries using the Arduino IDE Library Manager:

1. **U8g2** by olikraus — for the OLED display.
2. **ZMPT101B** — a compatible library that supports `getRmsVoltage()` and `setSensitivity()`.

## Software Setup

1. Install the Arduino IDE.
2. Install ESP32 board support through Boards Manager.
3. Install the required libraries listed above.
4. Open `esp32-ac-voltage-monitor.ino`.
5. Select your ESP32 board and the correct serial port.
6. Upload the sketch to your ESP32.
7. Open Serial Monitor at **115200 baud** to view voltage readings.

## Voltage Status Logic

The project uses the following voltage ranges:

| Measured AC Voltage | Display Status |
|---|---|
| 0–50V | OFF |
| Above 50V and below 120V | Voltage Error |
| 120V to below 180V | Low Voltage |
| 180–230V | OK |
| Above 230V | High Voltage |

These thresholds are configurable in the Arduino sketch.

## Calibration

The current example uses the following settings:

```cpp
#define SENSITIVITY 500.0f
#define CALIBRATION_FACTOR 1.49f
```

The calibration factor must be verified against a reliable AC voltmeter. Actual readings depend on the sensor module, its sensitivity adjustment, ADC behavior, and the selected library.

**Do not assume that a calibration factor that works at one voltage will be accurate across the full measurement range.**

## Example OLED Output

```text
AC VOLTAGE MONITOR
------------------
   AC Volt = 220V

      Status: OK
```

The voltage and status update continuously while the system is running.

## Safety Warning

This project involves potentially lethal mains AC voltage.

- Never connect mains AC directly to ESP32 GPIO pins.
- Never touch exposed mains wiring or live sensor terminals.
- Keep AC connections enclosed and insulated.
- Check the sensor module's ratings and isolation requirements.
- Verify that the sensor's low-voltage output is safe for the ESP32 before connecting it.
- Testing and calibration involving mains voltage should be performed by a qualified person using appropriate safety equipment.

This project is an educational prototype and should not be used as a certified safety device or a substitute for a properly rated voltage meter.

## Future Improvements

- Add under-voltage and over-voltage alarms.
- Add a graphical voltage history.
- Store minimum and maximum voltage readings.
- Add Wi-Fi monitoring and a web dashboard.
- Improve RMS sampling and calibration accuracy.

## License

This project is open source. Add a `LICENSE` file to specify the terms under which others may use, modify, and distribute your code.
