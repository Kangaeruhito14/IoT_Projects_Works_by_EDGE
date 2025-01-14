#include <Adafruit_SH110X.h>

extern Adafruit_SH1106G display;

// Soil Moisture Sensor Pins (for ESP-32, using suitable GPIO pins)
//#define SENSOR_POWER_PIN 23  // Example pin for power control, change as needed
#define SOIL_MOISTURE_SENSOR_PIN 35  // Example analog pin, change as needed

// Soil moisture thresholds (in VWC percentage)
const int SOIL_MOISTURE_THRESHOLDS[] = { 15, 30, 60, 85 };  // Dry, Moist, Wet, Very Wet

// Function to measure soil moisture
float measureSoilMoisture() {
  //digitalWrite(SENSOR_POWER_PIN, HIGH);  // Turn the sensor ON
  delay(10);  // Allow power to settle

  int sensorValue = analogRead(SOIL_MOISTURE_SENSOR_PIN);  // Read the soil moisture sensor value
  //digitalWrite(SENSOR_POWER_PIN, LOW);   // Turn the sensor OFF

  // ESP-32 uses 12-bit ADC, so the range is from 0 to 4095
  float voltage = sensorValue * (3.3 / 4095.0);  // Convert to voltage
  float soilMoisture = (voltage - 0.5) * 100.0;  // Adjust based on sensor calibration

  return soilMoisture;  // Return soil moisture in VWC percentage
}

void displaySoilCondition(float soilMoisture) {

  // Display soil moisture value
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Moist: ");
  display.print(soilMoisture, 2);
  display.print(" %");

  // Show soil state based on soil moisture value
  display.setCursor(0, 20);
  if (soilMoisture <= SOIL_MOISTURE_THRESHOLDS[0]) display.println("State: Dry");
  else if (soilMoisture <= SOIL_MOISTURE_THRESHOLDS[1]) display.println("State: Moist");
  else if (soilMoisture <= SOIL_MOISTURE_THRESHOLDS[2]) display.println("State: Wet");
  else display.println("State: Very Wet");

  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 40);
  display.println("> Back");

  display.display();
}

// Function to display soil quality on the OLED
void soilQualityMeasure() {

  while (currentMenu == 3) {  // Stay in Water Quality mode until "Back" is pressed
    // Check if "Back" button is pressed
    if (digitalRead(BACK_BUTTON) == LOW) {
      currentMenu = 0;  // Return to Main Menu
      showMainMenu();
      delay(300);  // Debounce
      break;       // Exit the loop
    }

    float soilMoisture = 0.00;
    soilMoisture = measureSoilMoisture();  // Measure soil moisture

    displaySoilCondition(soilMoisture);  // Display soil moisture value

    delay(1000);  // Wait for 1 second before finishing
  }
  // Return to the main menu or display (implement logic for the "back" button if needed)
}