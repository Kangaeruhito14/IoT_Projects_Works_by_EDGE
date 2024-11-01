#include <smart_duty_cycling.h>
smart_duty_cycling cycle;

int ledPin = 9; // Use a PWM-capable pin, e.g., 9 or 10
int brightness = 0; // Start with no brightness
int fadeAmount = 5; // Increment or decrement brightness

void setup() {
  Serial.begin(9600);
  cycle.setWakeSleepPeriods(4000, 1000); // Wake and Sleep period respectively in milliseconds
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (cycle.switchMode()) {
    if (cycle.wake) {
      // Perform operation in Wake / Active / ON time
      analogWrite(ledPin, brightness); // Set brightness level
      brightness += fadeAmount; // Change brightness for the next loop

      // Reverse fade direction at limits
      if (brightness <= 0 || brightness >= 255) {
        fadeAmount = -fadeAmount; 
      }

      delay(30); // Control fade speed
    } else {
      // Perform operation in Sleep / Inactive / OFF time
      analogWrite(ledPin, 0); // Turn off LED
    }
  }
}