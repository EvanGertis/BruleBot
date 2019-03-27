/*

*/

#include <Servo.h>


Servo panMotor;


void setup() {
  panMotor.attach(6);
  panMotor.write(90);
  
  Serial.begin(9600);
  Serial.println("This monitor will show us which way the servo motor has turned");
    
}

void loop() {
    panMotor.write(0); // turn to the right
    Serial.println("right");
    delay(500);
    panMotor.write(180);
    Serial.println("Center");
    delay(500);
    panMotor.write(90);
    Serial.println("Center");
    
}
