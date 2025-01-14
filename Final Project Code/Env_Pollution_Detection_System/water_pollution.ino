#include <Adafruit_SH110X.h>

extern Adafruit_SH1106G display;
// Turbidity Sensor Pin (for ESP-32, using a suitable analog pin)
#define TURBIDITY_SENSOR_PIN 34  // Example pin, change as necessary

// Function to measure turbidity
float measureTurbidity() {
  float sensorValue = analogRead(TURBIDITY_SENSOR_PIN);  // Read the turbidity sensor value
  float turbidity = map(sensorValue, 0, 1500, 100, 0);   // Adjust based on sensor calibration (ESP-32 uses 12-bit ADC)

  return turbidity;
}

void displayWaterTurbidity(float turbidity) {

  // Display turbidity value
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Tbdty: ");
  display.print(turbidity, 2);
  display.print(" NTU");

  // Show water quality state based on turbidity value
  display.setCursor(0, 20);
  if (turbidity <= 20) display.println("State: Good");
  else if (turbidity <= 50) display.println("State: Moderate");
  else if (turbidity <= 80) display.println("State: Poor");
  else display.println("State: Very Poor");

  display.setTextSize(1);
  display.setTextColor(SH110X_WHITE);
  display.setCursor(0, 40);
  display.println("> Back");

  display.display();
  
}

// Main water quality measurement function
void waterQualityMeasure() {
  while (currentMenu == 2) {  // Stay in Water Quality mode until "Back" is pressed
    // Check if "Back" button is pressed
    if (digitalRead(BACK_BUTTON) == LOW) {
      currentMenu = 0;  // Return to Main Menu
      showMainMenu();
      delay(300);  // Debounce
      break;       // Exit the loop
    }
    float turbidity = 0.00;
    turbidity = measureTurbidity(); // Measure turbidity

    displayWaterTurbidity(turbidity); // Display turbidity value

    delay(1000);
  }
  // Return to the main menu or display (implement logic for the "back" button if needed)
}