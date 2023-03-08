/* Servo motor with Arduino example code. Position and sweep. More info: https://www.makerguides.com/ */

// 80 is open

// Include the servo library:
#include <Servo.h>

// Create a new servo object:
Servo myservo;

// Define the servo pin:
#define servoPin 4

// Create a variable to store the servo position:
int angle = 0;

void setup() {
  // Attach the Servo variable to a pin:
  myservo.attach(servoPin);
}

void loop() {
  myservo.write(25);
  delay(2000);
  myservo.write(75);
  delay(2000);
}