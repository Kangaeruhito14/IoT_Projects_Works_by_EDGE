#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define i2c_Address 0x3c // initialize with the I2C addr 0x3C for eBay OLEDs
#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels
#define OLED_RESET -1     // QT-PY / XIAO

Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int sensorPin = A0;
int sensorData;

void setup() {
  Serial.begin(9600);
  pinMode(sensorPin, INPUT);

  // Initialize OLED display
  if (!display.begin(i2c_Address, true)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
}

void loop() {
  // Read MQ-135 sensor data
  sensorData = analogRead(sensorPin);

  // Determine air quality level
  String airQuality;
  if (sensorData < 300) {
    airQuality = "Good Air";
  } else if (sensorData < 600) {
    airQuality = "Moderate Air";
  } else {
    airQuality = "Bad Air";
  }

  // Print sensor data to Serial Monitor
  Serial.print("Air Quality: ");
  Serial.print(sensorData);
  Serial.print(" PPM - ");
  Serial.println(airQuality);

  // Display data on OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Air Quality Monitor");
  display.setCursor(0, 15);
  display.print("Sensor Value: ");
  display.print(sensorData);
  display.println(" PPM");
  display.setCursor(0, 35);
  display.print("Status: ");
  display.println(airQuality);
  display.display();

  delay(500);
}