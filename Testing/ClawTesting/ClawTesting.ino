#include <Servo.h>
Servo claw;
const int clawPin = 4;
const int clawCloseVal = 5;
const int clawOpenVal = 100;
void setup() {
  claw.attach(clawPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  claw.write(clawCloseVal);
  claw.writeMicroseconds();
  delay(2000);
  claw.write(clawOpenVal);
  delay(2000);
}

void openClaw(){
  claw.write(clawOpenVal);
  delay(1000);
  claw.write(clawCloseVal);
}
