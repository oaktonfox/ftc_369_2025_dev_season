#include <Adafruit_PWMServoDriver.h>
#include <stdio.h>
#include <stdlib.h> // Required for rand() and srand()
#include <time.h>   // Required for time()
Adafruit_PWMServoDriver board1 = Adafruit_PWMServoDriver(0x40);       // called this way, it uses the default address 0x40   

#define SERVOMIN  125                                                 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  625                                                 // this is the 'maximum' pulse length count (out of 4096)

const int number_of_servos = 8;
int direction_array[number_of_servos];
int servo_angle;
int angle_increment = 10;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");
  board1.begin();
  board1.setPWMFreq(60);                  // Analog servos run at ~60 Hz updates

}

void loop() { 

    // Generate a random number (0 or 1)
  for(int i=0; i<number_of_servos;i++){
    direction_array[i] = directionCode();
    Serial.println(direction_array[i]);
  }

  
// if direction is 1, starting is 180, and end is 0
// if direction is -1, starting is 0, and end is 180
  for(int i=0; i<number_of_servos; i++){
    board1.setPWM(i, 0, angleToPulse(90+90*direction_array[i]));
  }
  delay(1000);
    
  for( int angle =0; angle<181; angle +=angle_increment){
    for(int i=0; i<number_of_servos; i++){
        servo_angle = 90+90*direction_array[i] - angle*direction_array[i]; 
        board1.setPWM(i, 0, angleToPulse(servo_angle) );
      }
  }
  delay(100);
}

int angleToPulse(int ang)                             //gets angle in degree and returns the pulse width
  {  int pulse = map(ang,0, 180, SERVOMIN,SERVOMAX);  // map angle of 0 to 180 to Servo min and Servo max 
     Serial.print("Angle: ");Serial.println(ang);
     //Serial.print(" pulse: ");Serial.println(pulse);
     return pulse;
  }

int directionCode() {
    int random_binary = rand() % 2 ;

    // Map to -1 or 1
    int result = (random_binary == 0) ? -1 : 1;
    //Serial.print("Random binary: ");Serial.println(random_binary);
    //Serial.print("Random negative or positive 1: ");Serial.println(result);
    return result;
}

