int sensorPin = A0; // Select the input pin for LDR
int ledPin = 13;    // Select the output pin for LED
int sensorValue = 0; // Variable to store the value from the sensor

void setup() {
  Serial.begin(9600); // Set up serial communication
  pinMode(ledPin, OUTPUT); // Set the LED pin as an output
}

void loop() {
  sensorValue = analogRead(sensorPin); // Read the value from the sensor
  Serial.println(sensorValue); // Print the sensor value to the serial monitor

  if (sensorValue > 500) { // Adjust 500 as needed based on your threshold
    digitalWrite(ledPin, LOW); // Turn off LED if sensor value is high
  } else {
    digitalWrite(ledPin, HIGH); // Turn on LED if sensor value is low
  }

  delay(100); // Short delay before the next reading
}
