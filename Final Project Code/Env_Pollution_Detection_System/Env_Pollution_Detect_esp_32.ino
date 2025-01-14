#define BLYNK_TEMPLATE_ID "TMPL684fAqtpL"
#define BLYNK_TEMPLATE_NAME "Environmental Pollution Detection System"
#define BLYNK_AUTH_TOKEN "kOW5sSmJnb1Ij71p3ReKJvhI066o974l"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "Amal";        // type your wifi name
char pass[] = "ap1484480@";  // type your wifi password

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "DHT.h"

// OLED Display Setup
#define i2c_Address 0x3c
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SH1106G display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Button Pins for Navigation
#define UP_BUTTON 18
#define DOWN_BUTTON 19
#define MIDDLE_BUTTON 5
#define BACK_BUTTON 4

// Variables for Menu Navigation
int currentMenu = 0;  // 0: Main Menu, 1: Air Quality, 2: Water Quality, 3: Soil Quality
int selectedSubPart = 0;

void setup() {
  // Initialize Serial Communication
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);
  // Initialize OLED Display
  if (!display.begin(i2c_Address, true)) {
    while (true)
      ;  // Loop forever if display initialization fails
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.display();

  showWelcomeScreen();  // Show Welcome Message

  // Initialize Buttons
  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(MIDDLE_BUTTON, INPUT_PULLUP);
  pinMode(BACK_BUTTON, INPUT_PULLUP);

  // Show Main Menu
  showMainMenu();
}

void loop() {
  Blynk.run();

  // Continuous data transmission to Blynk cloud
  sendContinuousDataToBlynk();

  if (currentMenu == 0) {  // Main Menu Logic
    if (digitalRead(UP_BUTTON) == LOW) {
      selectedSubPart = max(0, selectedSubPart - 1);
      showMainMenu();
      delay(300);  // Debounce
    }

    if (digitalRead(DOWN_BUTTON) == LOW) {
      selectedSubPart = min(3, selectedSubPart + 1);  // 4 options (0-3)
      showMainMenu();
      delay(300);  // Debounce
    }

    if (digitalRead(MIDDLE_BUTTON) == LOW) {
      currentMenu = selectedSubPart + 1;  // Enter Subpart
      delay(300);                         // Debounce
    }

    if (digitalRead(BACK_BUTTON) == LOW) {
      showMainMenu();  // Back to Main Menu
      delay(300);      // Debounce
    }
  } else {
    // Subpart Logic
    if (currentMenu == 1) {         // Air Quality
      airQualityMeasure();          // Continuously measure
    } else if (currentMenu == 2) {  // Water Quality
      waterQualityMeasure();        // Continuously measure
    } else if (currentMenu == 3) {  // Soil Quality
      soilQualityMeasure();         // Continuously measure
    }

    if (digitalRead(BACK_BUTTON) == LOW) {
      currentMenu = 0;  // Return to Main Menu
      showMainMenu();
      delay(300);  // Debounce
    }
  }
}

void sendContinuousDataToBlynk() {
  static unsigned long lastSendTime = 0;
  const unsigned long sendInterval = 1000;  // Interval for sending data (1 second)

  // Only send data at the specified interval
  if (millis() - lastSendTime >= sendInterval) {
    lastSendTime = millis();

    // Air Quality Data
    float AQI, NH3, NOX, CO2, Benzene, SO2, CH4, LPG, Propane, H2, CO, Smoke, Alcohol, dustDensity;
    calculateAQI(AQI, NH3, NOX, CO2, Benzene, SO2, CH4, LPG, Propane, H2, CO, Smoke, Alcohol, dustDensity);
    Blynk.virtualWrite(V0, AQI);  // Replace V1 with the appropriate Blynk virtual pin

    // Water Quality Data
    float turbidity = 0.00;
    turbidity = measureTurbidity();  // Example function to calculate turbidity
    Blynk.virtualWrite(V1, turbidity);  // Replace V3 with the appropriate Blynk virtual pin

    // Soil Quality Data
    float soilMoisture = 0.00;
    soilMoisture = measureSoilMoisture();  // Example function to calculate soil moisture
    Blynk.virtualWrite(V2, soilMoisture);  // Replace V4 with the appropriate Blynk virtual pin
  }
}

// Show Welcome Screen
void showWelcomeScreen() {
  display.clearDisplay();
  display.setCursor(0, 20);
  display.print("Welcome to");
  display.setCursor(0, 30);
  display.print("Environmental Pollution");
  display.setCursor(0, 40);
  display.print("Detection System");
  display.display();
  delay(3000);
}

// Show Main Menu

void showMainMenu() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Main Menu:");

  display.setCursor(0, 10);
  display.print(selectedSubPart == 0 ? "> Air Quality" : "  Air Quality");

  display.setCursor(0, 20);
  display.print(selectedSubPart == 1 ? "> Water Quality" : "  Water Quality");

  display.setCursor(0, 30);
  display.print(selectedSubPart == 2 ? "> Soil Quality" : "  Soil Quality");

  display.display();
}