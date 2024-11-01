#define encoderPinA 2  // Pin A of the rotary encoder
#define encoderPinB 3  // Pin B of the rotary encoder
#define switchPin 4    // Switch pin of the rotary encoder

int encoderPosition = 0;  // Variable to store the position
int lastEncoded = 0;      // Last encoder state
bool switchState = HIGH;  // Current state of the switch
bool lastSwitchState = HIGH;  // Previous state of the switch

void setup() {
  pinMode(encoderPinA, INPUT);
  pinMode(encoderPinB, INPUT);
  pinMode(switchPin, INPUT_PULLUP);  // Enable pull-up resistor for switch pin
  Serial.begin(9600);

  // Enable internal pull-up resistors
  digitalWrite(encoderPinA, HIGH);
  digitalWrite(encoderPinB, HIGH);

  // Attach interrupts for the encoder pins
  attachInterrupt(digitalPinToInterrupt(encoderPinA), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderPinB), updateEncoder, CHANGE);
}

void loop() {
  // Check if the switch is pressed
  switchState = digitalRead(switchPin);
  
  // If switch was pressed (detecting a change from HIGH to LOW)
  if (switchState == LOW && lastSwitchState == HIGH) {
    encoderPosition = 0;  // Reset encoder position
    Serial.println("Switch pressed: Position reset to 0");
  }

  lastSwitchState = switchState;  // Update the last switch state

  // Display the encoder position
  Serial.print("Position: ");
  Serial.println(encoderPosition);
  delay(100);  // Adjust delay as needed
}

void updateEncoder() {
  int MSB = digitalRead(encoderPinA);  // Get the state of A
  int LSB = digitalRead(encoderPinB);  // Get the state of B

  int encoded = (MSB << 1) | LSB;      // Combine the A and B values
  int sum = (lastEncoded << 2) | encoded;  // Determine the direction

  if (sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
    encoderPosition++;
  if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000)
    encoderPosition--;

  lastEncoded = encoded;  // Store the last state
}