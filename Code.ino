
#include <Arduino.h>
#include <U8g2lib.h>
#include <ZMPT101B.h>

#define SENSITIVITY 500.0f
#define CALIBRATION_FACTOR 1.49f

// ZMPT101B sensor: GPIO 27, AC frequency: 50 Hz
ZMPT101B voltageSensor(27, 50.0);

// SPI OLED pins: SCK, MOSI, CS, DC, RESET
// Assumes a 128x64 SSD1306-compatible OLED
U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(
  U8G2_R0, 18, 23, 5, 16, 17
);

float voltage = 0.0f;

const char* getStatus(float v) {
  if (v <= 50.0f)  return "Status: OFF";
  if (v < 120.0f)  return "Voltage Error";
  if (v < 180.0f)  return "Low Voltage";
  if (v <= 230.0f) return "Status: OK";
  return "High Voltage";
}

void drawCentered(int y, const char* text) {
  int x = (128 - u8g2.getStrWidth(text)) / 2;
  u8g2.drawStr(x, y, text);
}

void setup() {
  Serial.begin(115200);

  voltageSensor.setSensitivity(SENSITIVITY);

  u8g2.begin();
  u8g2.setFont(u8g2_font_6x12_tf);

  u8g2.clearBuffer();
  drawCentered(25, "AC Voltage Monitor");
  drawCentered(45, "Starting...");
  u8g2.sendBuffer();

  delay(1000);
}

void loop() {
  // Read AC RMS voltage using your sensor code
  voltage = voltageSensor.getRmsVoltage()
            * CALIBRATION_FACTOR;

  // Format voltage text
  char voltageText[24];
  snprintf(
    voltageText,
    sizeof(voltageText),
    "AC Volt = %.0fV",
    voltage
  );

  const char* status = getStatus(voltage);

  // Update OLED
  u8g2.clearBuffer();

  u8g2.setFont(u8g2_font_6x12_tf);
  drawCentered(12, "AC VOLTAGE MONITOR");
  u8g2.drawHLine(8, 18, 112);

  u8g2.setFont(u8g2_font_helvB10_tf);
  drawCentered(39, voltageText);

  u8g2.setFont(u8g2_font_6x12_tf);
  drawCentered(57, status);

  u8g2.sendBuffer();

  // Also print the reading in Serial Monitor
  Serial.print("Voltage: ");
  Serial.print(voltage, 1);
  Serial.print(" V | ");
  Serial.println(status);

  delay(200);
}