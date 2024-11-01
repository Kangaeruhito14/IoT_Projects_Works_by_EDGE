int relay_1 = 4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(relay_1, OUTPUT);

}

void loop() {

  digitalWrite(relay_1, LOW);

  Serial.println("Relay 1 on");

  delay(2500);

  digitalWrite(relay_1, HIGH);

  Serial.println("Relay 1 off");

  delay(2500);
}