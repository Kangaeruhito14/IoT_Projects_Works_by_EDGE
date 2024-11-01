// Define the LED pin (default is built-in LED on GPIO 2 for ESP8266)
#define LED_PIN 2

void setup() {
  // Initialize the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Turn the LED on
  digitalWrite(LED_PIN, LOW); // LOW is ON for built-in LED
  delay(1000); // Wait for 1 second
  
  // Turn the LED off
  digitalWrite(LED_PIN, HIGH); // HIGH is OFF for built-in LED
  delay(1000); // Wait for 1 second
}
