int sensorPin=A0;
int sensorData;
void setup()
{  
  Serial.begin(9600);   
  pinMode(sensorPin,INPUT);                         
 }
void loop()
{
  sensorData = analogRead(sensorPin);       
  Serial.print("Air Quality:");
  Serial.print(sensorData, DEC);               
  Serial.println(" PPM");
  delay(500);                                   
}