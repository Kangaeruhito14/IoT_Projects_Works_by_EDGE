#define sensor_pin A0 
int read_ADC;
int ntu;

void setup() {
  pinMode(sensor_pin, INPUT);
  Serial.begin(9600);  // Initialize serial communication
  delay(2000);         // Allow some time for sensor stabilization

  // Initial welcome message
  Serial.println("Welcome to Turbidity Sensor");
  Serial.println("Initializing...");
  delay(2000);
}

void loop() {
  read_ADC = analogRead(sensor_pin);
  
  // Cap the reading at 208 to avoid out-of-range values
  if (read_ADC > 208) read_ADC = 208;

  // Map the sensor reading to NTU range
  ntu = map(read_ADC, 0, 208, 300, 0); 

  // Print turbidity reading
  Serial.print("Turbidity (NTU): ");
  Serial.println(ntu);

  // Print water quality status
  if (ntu < 50) {
    Serial.println("Status: Water Very Clean");
  } else if (ntu >= 50 && ntu < 100) {
    Serial.println("Status: Water Normally Clean");
  } else {
    Serial.println("Status: Water Very Dirty");
  }

  Serial.println();  // Add a blank line for readability
  delay(1000);       // Delay before next reading
}