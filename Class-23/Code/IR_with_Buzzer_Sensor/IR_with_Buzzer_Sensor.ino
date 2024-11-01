int irSensor = 2;
int buzzer = 3;
void setup()
{
  Serial.begin(9600);
  pinMode(irSensor, INPUT);
  pinMode(buzzer, OUTPUT);
}
void loop()
{
  int value = digitalRead(irSensor);
  Serial.println("");
  Serial.print("Sensor Value = ");
  Serial.print(value);
  
  if(value == 0)
  {
    digitalWrite(buzzer, HIGH);
  }
  else
  {
    digitalWrite(buzzer, LOW);
  }
  delay(50);
}