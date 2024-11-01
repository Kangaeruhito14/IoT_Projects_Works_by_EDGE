const int sensorPin = A3;

void setup(){
  Serial.begin(9600);
  Serial.println("Distance Measurement (MD1030): ");
}

void loop(){
  int sensorValue = analogRead(sensorPin);
  float voltage = sensorValue * (5.0 / 1024.0);
  float distance = voltage * 512;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  Serial.print("Voltage: ");
  Serial.print(voltage);
  Serial.println(" V");
  Serial.println("");
  delay(500);
}