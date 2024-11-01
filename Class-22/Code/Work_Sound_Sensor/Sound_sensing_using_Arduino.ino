int micPin = A0;
//int digitalPin = 52;
int sensorValue = 0;
int DigitalState = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  //pinMode(digitalPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(micPin);
  //DigitalState = digitalRead(digitalPin);
  Serial.println(sensorValue, DEC);
  //Serial.println(DigitalState);

  if (sensorValue >= 250) {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(3000);
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(1000);
    // digitalWrite(LED_BUILTIN, LOW);
    // delay(50);
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(50);
    // digitalWrite(LED_BUILTIN, LOW);
    // delay(50);
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(50);
    // digitalWrite(LED_BUILTIN, LOW);
    // delay(50);
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(50);
    // digitalWrite(LED_BUILTIN, LOW);
    // delay(50);
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(50);
    // digitalWrite(LED_BUILTIN, LOW);
    // delay(50);
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(50);
    // digitalWrite(LED_BUILTIN, LOW);
    // delay(50);
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(50);
    // digitalWrite(LED_BUILTIN, LOW);
    // delay(50);
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(50);
    // digitalWrite(LED_BUILTIN, LOW);
    // delay(50);
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(50);
    // digitalWrite(LED_BUILTIN, LOW);
    // delay(50);
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(50);
    // digitalWrite(LED_BUILTIN, LOW);
    // delay(50);
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(50);
    // digitalWrite(LED_BUILTIN, LOW);
    // delay(50);
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(50);
    // digitalWrite(LED_BUILTIN, LOW);
    // delay(50);
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(50);
    // digitalWrite(LED_BUILTIN, LOW);
    // delay(50);
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(50);
    // digitalWrite(LED_BUILTIN, LOW);
    // delay(50);
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(50);
    // digitalWrite(LED_BUILTIN, LOW);
    // delay(50);
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(50);
    // digitalWrite(LED_BUILTIN, LOW);
    // delay(50);
    // digitalWrite(LED_BUILTIN, HIGH);
    // delay(1500);

  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}