#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

// OLED display setup
extern Adafruit_SH1106G display;

// Sensor pins for ESP-32
#define MQ135_PIN 39     // Assigning to ADC1 channel (GPIO34)
#define MQ2_PIN 36       // Assigning to ADC1 channel (GPIO35)
#define DUST_SENSOR_LED_PIN 32  // Assign a digital pin
#define DUST_SENSOR_AO_PIN 33   // Assign a digital pin for dust sensor analog out

// Factors for gases (MQ135 and MQ2)
#define NH3_FACTOR 0.2
#define NOX_FACTOR 0.3
#define CO2_FACTOR 0.4
#define BENZENE_FACTOR 0.5
#define SO2_FACTOR 0.6
#define CH4_FACTOR 0.25
#define LPG_FACTOR 0.30
#define PROPANE_FACTOR 0.35
#define H2_FACTOR 0.40
#define CO_FACTOR 0.55
#define SMOKE_FACTOR 0.45
#define ALCOHOL_FACTOR 0.50

// Dust sensor constants
#define VOC 0.6    // Adjust this based on calibration
#define SLOPE 0.5  // Adjust this based on calibration

// Function to calculate AQI and sensor values
void calculateAQI(float &AQI, float &NH3, float &NOX, float &CO2, float &Benzene, float &SO2,
                  float &CH4, float &LPG, float &Propane, float &H2, float &CO, float &Smoke,
                  float &Alcohol, float &dustDensity) {
  // MQ135 readings
  int mq135Raw = analogRead(MQ135_PIN);
  float RS_MQ135 = mq135Raw * (3.3 / 4095.0);
  NH3 = RS_MQ135 * NH3_FACTOR;
  NOX = RS_MQ135 * NOX_FACTOR;
  CO2 = RS_MQ135 * CO2_FACTOR;
  Benzene = RS_MQ135 * BENZENE_FACTOR;
  SO2 = RS_MQ135 * SO2_FACTOR;

  // MQ2 readings
  int mq2Raw = analogRead(MQ2_PIN);
  float RS_MQ2 = mq2Raw * (3.3 / 4095.0);
  CH4 = RS_MQ2 * CH4_FACTOR;
  LPG = RS_MQ2 * LPG_FACTOR;
  Propane = RS_MQ2 * PROPANE_FACTOR;
  H2 = RS_MQ2 * H2_FACTOR;
  CO = RS_MQ2 * CO_FACTOR;
  Smoke = RS_MQ2 * SMOKE_FACTOR;
  Alcohol = RS_MQ2 * ALCOHOL_FACTOR;

  // Dust sensor readings
  digitalWrite(DUST_SENSOR_LED_PIN, LOW);
  delayMicroseconds(280);
  int dustRaw = analogRead(DUST_SENSOR_AO_PIN);
  delayMicroseconds(40);
  digitalWrite(DUST_SENSOR_LED_PIN, HIGH);
  float dustVoltage = dustRaw * (3.3 / 4095.0);
  dustDensity = (dustVoltage - VOC) / SLOPE * 100.0;

  // Breakpoint tables for each pollutant (example values, replace with official data)
  const float NH3_Breakpoints[][4] = {{0, 200, 0, 50}, {200, 400, 51, 100}, {400, 800, 101, 200}};
  const float NOX_Breakpoints[][4] = {{0, 100, 0, 50}, {100, 200, 51, 100}, {200, 400, 101, 200}};
  const float CO2_Breakpoints[][4] = {{0, 5000, 0, 50}, {5000, 10000, 51, 100}, {10000, 20000, 101, 200}};
  const float Benzene_Breakpoints[][4] = {{0, 50, 0, 50}, {50, 100, 51, 100}, {100, 200, 101, 200}};
  const float SO2_Breakpoints[][4] = {{0, 100, 0, 50}, {100, 200, 51, 100}, {200, 400, 101, 200}};
  const float CH4_Breakpoints[][4] = {{0, 100, 0, 50}, {100, 200, 51, 100}, {200, 400, 101, 200}};
  const float LPG_Breakpoints[][4] = {{0, 100, 0, 50}, {100, 200, 51, 100}, {200, 400, 101, 200}};
  const float Propane_Breakpoints[][4] = {{0, 100, 0, 50}, {100, 200, 51, 100}, {200, 400, 101, 200}};
  const float H2_Breakpoints[][4] = {{0, 100, 0, 50}, {100, 200, 51, 100}, {200, 400, 101, 200}};
  const float CO_Breakpoints[][4] = {{0, 10, 0, 50}, {10, 20, 51, 100}, {20, 30, 101, 200}};
  const float Smoke_Breakpoints[][4] = {{0, 100, 0, 50}, {100, 200, 51, 100}, {200, 400, 101, 200}};
  const float Alcohol_Breakpoints[][4] = {{0, 100, 0, 50}, {100, 200, 51, 100}, {200, 400, 101, 200}};
  const float Dust_Breakpoints[][4] = {{0, 50, 0, 50}, {51, 100, 51, 100}, {101, 250, 101, 200}};

  // Helper function to calculate sub-index
  auto calculateSubIndex = [](float C, const float breakpoints[][4], int rows) {
    for (int i = 0; i < rows; ++i) {
      if (C >= breakpoints[i][0] && C <= breakpoints[i][1]) {
        return (breakpoints[i][3] - breakpoints[i][2]) / (breakpoints[i][1] - breakpoints[i][0]) *
                   (C - breakpoints[i][0]) +
               breakpoints[i][2];
      }
    }
    return 0.0f;  // Return 0 if out of range
  };

  // Calculate sub-indices
  float NH3_AQI = calculateSubIndex(NH3, NH3_Breakpoints, 3);
  float NOX_AQI = calculateSubIndex(NOX, NOX_Breakpoints, 3);
  float CO2_AQI = calculateSubIndex(CO2, CO2_Breakpoints, 3);
  float Benzene_AQI = calculateSubIndex(Benzene, Benzene_Breakpoints, 3);
  float SO2_AQI = calculateSubIndex(SO2, SO2_Breakpoints, 3);
  float CH4_AQI = calculateSubIndex(CH4, CH4_Breakpoints, 3);
  float LPG_AQI = calculateSubIndex(LPG, LPG_Breakpoints, 3);
  float Propane_AQI = calculateSubIndex(Propane, Propane_Breakpoints, 3);
  float H2_AQI = calculateSubIndex(H2, H2_Breakpoints, 3);
  float CO_AQI = calculateSubIndex(CO, CO_Breakpoints, 3);
  float Smoke_AQI = calculateSubIndex(Smoke, Smoke_Breakpoints, 3);
  float Alcohol_AQI = calculateSubIndex(Alcohol, Alcohol_Breakpoints, 3);
  float Dust_AQI = calculateSubIndex(dustDensity, Dust_Breakpoints, 3);

  // Determine overall AQI (maximum of sub-indices)
  AQI = max({NH3_AQI, NOX_AQI, CO2_AQI, Benzene_AQI, SO2_AQI, CH4_AQI,
             LPG_AQI, Propane_AQI, H2_AQI, CO_AQI, Smoke_AQI, Alcohol_AQI, Dust_AQI});
}

// Function to display AQI data on the OLED
void displayAQIData(float AQI, float NH3, float NOX, float CO2, float Benzene, float SO2,
                    float CH4, float LPG, float Propane, float H2, float CO, float Smoke,
                    float Alcohol, float dustDensity, bool showData) {
  display.clearDisplay();

  if (showData) {
    // Main AQI display
    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 0);
    display.print("AQI: ");
    display.println(AQI, 1);

    display.setTextSize(1);
    display.setCursor(0, 20);
    if (AQI <= 50) display.println("Quality: Good");
    else if (AQI <= 100) display.println("Quality: Moderate");
    else if (AQI <= 150) display.println("Quality: Unhealthy");
    else if (AQI <= 200) display.println("Quality: Very Unhealthy");
    else display.println("Quality: Hazardous");

    display.setTextSize(1);
    display.setTextColor(SH110X_WHITE);
    display.setCursor(0, 40);
    display.println("> Back");
  }
  display.display();
}

void airQualityMeasure() {
  while (currentMenu == 1) {  // Stay in Air Quality mode until "Back" is pressed
    // Check if "Back" button is pressed
    if (digitalRead(BACK_BUTTON) == LOW) {
      currentMenu = 0;  // Return to Main Menu
      showMainMenu();
      delay(300);  // Debounce
      break;  // Exit the loop
    }

    // Declare variables to store AQI and sensor readings
    float AQI = 0;
    float NH3, NOX, CO2, Benzene, SO2, CH4, LPG, Propane, H2, CO, Smoke, Alcohol, dustDensity;

    // Calculate AQI and sensor data
    calculateAQI(AQI, NH3, NOX, CO2, Benzene, SO2, CH4, LPG, Propane, H2, CO, Smoke, Alcohol, dustDensity);

    // Display the AQI data on the OLED
    displayAQIData(AQI, NH3, NOX, CO2, Benzene, SO2, CH4, LPG, Propane, H2, CO, Smoke, Alcohol, dustDensity, true);

    delay(1000);  // Small delay for readability and to reduce excessive updates
  }
}
