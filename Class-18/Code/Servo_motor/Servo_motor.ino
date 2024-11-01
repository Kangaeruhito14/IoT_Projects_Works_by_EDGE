/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos;    // variable to store the servo position
void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
 myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(500);
    myservo.write(pos+60);              // tell servo to go to position in variable 'pos'
    delay(500);
    myservo.write(pos+90);              // tell servo to go to position in variable 'pos'
    delay(500);
  myservo.write(pos+60);              // tell servo to go to position in variable 'pos'
    delay(500);
    myservo.write(pos+30);              // tell servo to go to position in variable 'pos'
    delay(500);
}

// for (pos = 50; pos <= 110; pos += 20) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
 //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
 //   delay(500);                       // waits 15 ms for the servo to reach the position
 // }
 // for (pos =110; pos >=10 ; pos -= 20) { // goes from 180 degrees to 0 degrees
 //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
 //   delay(500);                       // waits 15 ms for the servo to reach the position
 // }