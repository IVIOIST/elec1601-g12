#include <Servo.h>

// Servo Pins
const int leftServoPin = 12;
const int rightServoPin = 13;

Servo leftServo;
Servo rightServo;

// Constants for servo control
const int SERVO_STOP = 1500;
const int SERVO_MAX_FORWARD = 1300;
const int SERVO_MAX_REVERSE = 1700;

// Variables for turn calibration
int turnSpeed = 30;  // Initial turn speed
int turnTime = 500;  // Initial turn time (in milliseconds)

void setup() {
  leftServo.attach(leftServoPin);
  rightServo.attach(rightServoPin);

  leftServo.writeMicroseconds(SERVO_STOP);
  rightServo.writeMicroseconds(SERVO_STOP);

  Serial.begin(9600);
  Serial.println("TurnRobot Function Calibration");
  Serial.println("Commands:");
  Serial.println("'l': Turn left 90 degrees");
  Serial.println("'r': Turn right 90 degrees");
  Serial.println("'+': Increase turn time by 50ms");
  Serial.println("'-': Decrease turn time by 50ms");
  Serial.println("'f': Increase turn speed by 5");
  Serial.println("'s': Decrease turn speed by 5");
  Serial.println("'t': Test full rotation (4 x 90 degree turns)");
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    switch (command) {
      case 'l':
        turnRobot(-90);
        break;
      case 'r':
        turnRobot(90);
        break;
      case '+':
        turnTime += 50;
        Serial.print("Turn time increased to: ");
        Serial.println(turnTime);
        break;
      case '-':
        turnTime -= 50;
        if (turnTime < 0) turnTime = 0;
        Serial.print("Turn time decreased to: ");
        Serial.println(turnTime);
        break;
      case 'f':
        turnSpeed += 5;
        if (turnSpeed > 100) turnSpeed = 100;
        Serial.print("Turn speed increased to: ");
        Serial.println(turnSpeed);
        break;
      case 's':
        turnSpeed -= 5;
        if (turnSpeed < 0) turnSpeed = 0;
        Serial.print("Turn speed decreased to: ");
        Serial.println(turnSpeed);
        break;
      case 't':
        testFullRotation();
        break;
    }
  }
}

void turnRobot(int angle) {
  Serial.print("Turning ");
  Serial.print(angle > 0 ? "right" : "left");
  Serial.print(" with speed ");
  Serial.print(turnSpeed);
  Serial.print(" for ");
  Serial.print(turnTime);
  Serial.println(" ms");

  int actualTurnTime = map(abs(angle), 0, 90, 0, turnTime);
  
  if (angle > 0) {
    moveRobot(-turnSpeed, turnSpeed);  // Turn right
  } else {
    moveRobot(turnSpeed, -turnSpeed);  // Turn left
  }
  
  delay(actualTurnTime);
  moveRobot(0, 0);  // Stop turning
}

void testFullRotation() {
  Serial.println("Testing full rotation (4 x 90 degree turns)");
  for (int i = 0; i < 4; i++) {
    turnRobot(90);
    delay(1000);  // Pause between turns
  }
  Serial.println("Full rotation test complete");
}

void moveRobot(int leftSpeed, int rightSpeed) {
  int leftMs = map(leftSpeed, -100, 100, SERVO_MAX_REVERSE, SERVO_MAX_FORWARD);
  int rightMs = map(rightSpeed, -100, 100, SERVO_MAX_FORWARD, SERVO_MAX_REVERSE);
  
  leftServo.writeMicroseconds(leftMs);
  rightServo.writeMicroseconds(rightMs);
}