// Servo - Version: Latest 
#include <Servo.h>

const int RForward = 120;
const int RBackward = 60;

const int LForward = 120;
const int LBackward = 60;

const int RNeutral = 90;
const int LNeutral = 90;

Servo leftMotor;
Servo rightMotor;

void setup() {
  
    rightMotor.attach(11);
    leftMotor.attach(10);
}

void loop() {
  

  
  // leftMotor.write(RNeutral);
  // rightMotor.write(LNeutral);
  
  // leftMotor.write(LForward);
  rightMotor.write(RForward);
  
  // leftMotor.write(LBackward);
  // rightMotor.write(RForward);
  
  // leftMotor.write(LForward);
  // rightMotor.write(RBackward);
  
  // leftMotor.write(LBackward);
  // rightMotor.write(RForward);
    
}
