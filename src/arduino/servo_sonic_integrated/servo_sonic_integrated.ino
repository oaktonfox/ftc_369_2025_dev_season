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
int step_delay = 30;
int current_pos;
int analogPin = A3; // potentiometer wiper (middle terminal) connected to analog pin 3
int val = 0;  // variable to store the value read

// SWYFT: 10-65
//Gobilda: 80-130
//Axon 20-90
int start_pos = 50;
int end_pos = 90;
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
    read_current_pos();
  }
  Serial.print("servo position: ");
  Serial.println(pos-1);
  distance = sonic_distance();
  
  for (pos = end_pos; pos >= start_pos; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo1.write(pos);  
         // tell servo to go to position in variable 'pos'
    delay(step_delay);                       // waits 15ms for the servo to reach the position
    read_current_pos();
  }

  Serial.println(pos+1);
  distance = sonic_distance();



}



void read_current_pos() {

  val = analogRead(analogPin); 
  current_pos = val*360/3.3;

  //Serial.print("servo current position: ");
  //Serial.println(current_pos);


}
int sonic_distance() {
  delay(200);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2;
  Serial.print("Sonic Distance: ");
  Serial.println(distance);
  //delay(200);
  return distance;
}