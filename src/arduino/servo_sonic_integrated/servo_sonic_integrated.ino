/*
 * HC-SR04 example sketch
 *
 * https://create.arduino.cc/projecthub/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-036380
 *
 * by Isaac100
 */

#include <Servo.h>

Servo myservo1;  // create servo object to control a servo

// servo parameters
int pos = 0;    // variable to store the servo position
int limit = 210;
int step_delay = 20;
int start_pos = 10;
int end_pos = 65;
const int servoPin = 11;

//sonic sensor parameters
const int trigPin = 9;
const int echoPin = 10;

float duration, distance;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  myservo1.attach(servoPin);  // attaches the servo on pin 9 to the servo object
}

void loop() {

    for (pos = start_pos; pos <= end_pos; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo1.write(pos);            // tell servo to go to position in variable 'pos'
    delay(step_delay);                       // waits 15ms for the servo to reach the position
  }
  Serial.print("servo position: ");
  Serial.println(pos-1);
  distance = sonic_distance();
  
  for (pos = end_pos; pos >= start_pos; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);               // tell servo to go to position in variable 'pos'
    delay(step_delay);                       // waits 15ms for the servo to reach the position
  }
  Serial.print("servo position: ");
  Serial.println(pos+1);
  distance = sonic_distance();


}

int sonic_distance() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
  return distance;
}