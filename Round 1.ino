#include <Servo.h>

// Pin connections
// pins for the front sensor
const int trigPin1 = 2;
const int echoPin1 = 3;
// pins for the right sensor
const int trigPin2 = 6;
const int echoPin2 = 7;
// pins for the left sensor
const int trigPin3 = 4;
const int echoPin3 = 5;
//pins for the motor
const int motorPin1 = A0;
const int motorPin2 = A1;

int enb = A2;

const int left = 10;
const int right = 90;
const int slightright = 65;
const int straight= 50;
// Servo and motor objects
Servo servo;
int motorSpeed = 180;  // Adjust this value to set the motor speed

// Ultrasonic sensor variables
long duration1;
int distance1;
long duration2;
int distance2;

void setup() {
  // Initialize pins
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enb, OUTPUT);

  // Attach servo to the corresponding pin
  servo.attach(11);
  servo.write(straight);  // Set servo to 90 degrees (initial position)

  // Start the motors
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  analogWrite(enb,180);
  delay(100);
}

void loop() {
  // Measure distance using sensor 1
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);

  duration1 = pulseIn(echoPin1, HIGH);
  distance1 = duration1 * 0.034 / 2;  // Calculate distance in centimeters
  digitalWrite(motorPin1,HIGH);
  digitalWrite(motorPin2, LOW);
  analogWrite(enb,250);
  // If an obstacle is detected within 30cm by sensor 1, stop the motor
  if (distance1 < 35) {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
    

    digitalWrite(trigPin2, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);

    // Read second ultrasonic sensor response
    duration2 = pulseIn(echoPin2, HIGH);
  
    // Calculate distance based on speed of soundT
    distance2 = duration2 * 0.034 / 2;

    if (distance2<40){

      turn(left);

    }
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);

    digitalWrite(trigPin2, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);

    // Read second ultrasonic sensor response
    duration2 = pulseIn(echoPin2, HIGH);
  
    // Calculate distance based on speed of sound
    distance2 = duration2 * 0.034 / 2;
    if (distance2>40){
      turn(right);
    }    
  }
  else{
    digitalWrite(motorPin1,HIGH);
    digitalWrite(motorPin2,LOW);
    servo.write(straight);
    analogWrite(enb,180);
  }
}

void turn(int direction){
      servo.write(direction);
      digitalWrite(motorPin1,HIGH);
      digitalWrite(motorPin2,LOW);
      analogWrite(enb,180);
      delay(780);
      servo.write(straight);
}
