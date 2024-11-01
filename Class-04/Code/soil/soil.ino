#define red 6
#define white 9

void setup() {
  Serial.begin(9600);          
  pinMode(red, OUTPUT);        
  pinMode(white, OUTPUT);      
}

void loop() {
  int sensorValue = analogRead(A0);  
  Serial.println(sensorValue);       
  
  if (sensorValue >= 500 && sensorValue <= 700) {
    digitalWrite(white, HIGH);      
    digitalWrite(red, LOW);         
  } 
  else if (sensorValue >= 0 && sensorValue < 500) {
    digitalWrite(white, LOW);       
    digitalWrite(red, HIGH);        
  } 
  else if (sensorValue >= 800 && sensorValue <= 1023) {
    digitalWrite(white, HIGH);      
    digitalWrite(red, HIGH);
  }    // Short delay to avoid flooding the serial monitor
}

