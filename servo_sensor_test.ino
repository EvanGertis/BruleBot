/*
Reads photosensor value at analog pin 2
*/

// Servo library.
#include <Servo.h>

// Constants for pins.
int sensorPinLeft = A0;
int sensorPinRight = A2;
int thresholdPin = A4;
int lightValueLeft = 0;
int lightValueRight = 0;
int thresholdValue = 0;
int ledPinLeft = 2;
int ledPinRight = 3;
int sensorDifference = 0;
int closeness = 25;
int pingPin = 5;
int moveTime = 500;

// Constant rotations for main driving servos.
const int RForward = 60;
const int RBackward = 120;

const int LForward = 120;
const int LBackward = 60;

const int RNeutral = 90;
const int LNeutral = 90;

// Main driving servos.
Servo leftMotor;
Servo rightMotor;

// Ultrasonic panning servo.
Servo panMotor;

void setup() {
  
  panMotor.attach(6);
  rightMotor.attach(11);
  leftMotor.attach(10);
  panMotor.write(0);

  Serial.begin(9600);
  Serial.println("This monitor will show us which way the servo motor has turned");
  pinMode(ledPinLeft, OUTPUT);
  pinMode(ledPinRight, OUTPUT);
    
}

void loop() {
  long duration, cm;
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  
  panServo();

  while(cm > 5){
      panServo();
      
      pinMode(pingPin, OUTPUT);
      digitalWrite(pingPin, LOW);
      delayMicroseconds(2);
      digitalWrite(pingPin, HIGH);
      delayMicroseconds(5);
      digitalWrite(pingPin, LOW);
      pinMode(pingPin, INPUT);
      duration = pulseIn(pingPin, HIGH);
  
      cm = microsecondsToCentimeters(duration);
      Serial.print(cm);
      Serial.print("cm");
      Serial.println();
  
      lightValueLeft = analogRead(sensorPinLeft);
      leftTurn();
      Serial.println(lightValueLeft);
      
      lightValueRight = analogRead(sensorPinRight);
      rightTurn();
      Serial.println(lightValueRight);
      
      thresholdValue = analogRead(thresholdPin);
      Serial.print("threshold value : ");
      Serial.println(thresholdValue);
      
      sensorDifference = abs(lightValueLeft - lightValueRight);
      Serial.print("sensorDifference : ");
      Serial.println(sensorDifference);
    
      // Forward procedure
      if( lightValueLeft   <= thresholdValue   &&
          lightValueRight  <= thresholdValue   &&
          sensorDifference <= closeness        &&
          lightValueLeft   >= thresholdValue/2 &&
          lightValueRight  >= thresholdValue/2){
            
            forwardMotion();
            digitalWrite(ledPinLeft, HIGH);
            digitalWrite(ledPinRight, HIGH);
            delay(moveTime);
            stopMotion();
          }
      else if(lightValueLeft   >= thresholdValue &&
              lightValueRight  >= thresholdValue &&
              sensorDifference <= closeness){
                stopMotion();
                digitalWrite(ledPinLeft, LOW);
                digitalWrite(ledPinRight, LOW);
                delay(moveTime);
                stopMotion();
              }
      else if(lightValueLeft > lightValueRight  &&
              sensorDifference > closeness      &&
              lightValueLeft >= thresholdValue  &&
              lightValueRight >= thresholdValue/2){
                rightTurn();
                digitalWrite(ledPinLeft, LOW);
                digitalWrite(ledPinRight, HIGH);
                delay(moveTime);
                stopMotion();
              }
      else if(lightValueRight > lightValueLeft && 
              sensorDifference > closeness     &&
              lightValueRight  >= thresholdValue &&
              lightValueLeft >= thresholdValue/2){
                leftTurn();
                digitalWrite(ledPinLeft, HIGH);
                digitalWrite(ledPinRight, LOW);
                delay(moveTime);
                stopMotion();
              }
      else{
                repositionMovement();
                stopMotion();
      }
  }
  repositionMovement();
  
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}

void repositionMovement(){
  Serial.println("LOST");
  reverseMotion();
  digitalWrite(ledPinLeft, LOW);
  digitalWrite(ledPinRight, LOW);
  leftTurn();
  digitalWrite(ledPinLeft, HIGH);
  digitalWrite(ledPinRight, HIGH);
  rightTurn();
  forwardMotion();
}

void panServo(){
  panMotor.write(0); // turn to the right
  Serial.println("right");
  delay(500);
  panMotor.write(180);
  Serial.println("Left");
  delay(500);
  panMotor.write(90);
  Serial.println("Center");
  delay(500);
}

void stopMotion(){
  leftMotor.write(RNeutral);
  rightMotor.write(LNeutral);
}

void forwardMotion(){
  leftMotor.write(LForward);
  rightMotor.write(RBackward);
}

void reverseMotion(){
  leftMotor.write(LBackward);
  rightMotor.write(RForward);
}

void leftTurn(){
  leftMotor.write(LForward);
  rightMotor.write(RForward);
}

void rightTurn(){
  leftMotor.write(LBackward);
  rightMotor.write(RBackward);
}