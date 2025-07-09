#include <Servo.h>

Servo myservo1;  // create servo object to control a servo

// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int limit = 210;
int step_delay = 20;
int start_pos = 10;
int end_pos = 65;

void setup() {
  Serial.begin(9600);
  myservo1.attach(11);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  for (pos = start_pos; pos <= end_pos; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo1.write(pos);            // tell servo to go to position in variable 'pos'
    delay(step_delay);                       // waits 15ms for the servo to reach the position
  }
  Serial.print(pos);
  Serial.println();
  for (pos = end_pos; pos >= start_pos; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);               // tell servo to go to position in variable 'pos'
    delay(step_delay);                       // waits 15ms for the servo to reach the position
  }
  Serial.print(pos);
  Serial.println();
  /*
    myservo1.write(45);
  while(1)
  {};
  */

}