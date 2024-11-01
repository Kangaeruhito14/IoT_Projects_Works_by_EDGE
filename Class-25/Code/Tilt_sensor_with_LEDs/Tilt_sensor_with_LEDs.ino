// Define pin numbers for the LEDs
const int led1 = 4;
const int led2 = 7;

// Tilt sensor pin
const int tiltSensorPin = A0; // Analog pin to which the tilt sensor is connected
int tiltValue; // Variable to store the tilt sensor value

void setup() {
  // Set LED pins as outputs
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);

  // Initialize serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read the value from the tilt sensor
  tiltValue = analogRead(tiltSensorPin);
  Serial.println(tiltValue); // Print the value for debugging
  
  // Turn on one LED at a time based on the tilt sensor reading
  if (tiltValue < 500) {         // Tilt position 1
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
  } else {                       // other position
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
  }

  delay(100); // Small delay for stability
}
