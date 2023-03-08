//2023 FIASCO Robot Controller Sketch

//imports
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <Servo.h>

// radio setup
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
const int radioChannel = 1;

//Robot Control Objects + Pins
Servo left;
Servo right;
Servo claw;

const int leftServoPin = 2;
const int rightServoPin = 3;
const int clawPin = 4;
const int ledPin = 5;

//Servo values
const int rightStopValue = 95;
const int leftStopValue = 94;
const int leftForwardVal = 0;
const int rightForwardVal = 180;
const int leftBackVal = 180;
const int rightBackVal = 0;
const int clawCloseVal = 75;
const int clawOpenVal = 25;


//Serial Commands
const int SerialBaudRate = 9600;



//list of commands, to help translate recieved indexes
//update both length and values as necessary
const int messageLength = 6;
const String messages[messageLength] = {
  "GRAB",
  "FORWARD",
  "LEFT",
  "RIGHT",
  "BACK",
  "RELEASE"
};


void setup() {
  //initialize serial
  Serial.begin(SerialBaudRate);
  //radio setup
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(radioChannel);
  radio.startListening();
  radio.printDetails();

  //initialize robot controller pins
  left.attach(leftServoPin); 
  right.attach(rightServoPin);
  claw.attach(clawPin);
  claw.write(clawCloseVal);
  //set initial direction to center and initial speed to 0
  stop();
  //led setup
  pinMode(ledPin,OUTPUT);
}


void loop() {
  //read radio to see if messages are sent
  if (radio.available()) {
    unsigned long received = 1000;
    radio.read(&received, sizeof(unsigned long));
    if (received >= 0 && received <= 999){
      //change indicator led state
      digitalWrite(ledPin,LOW);
      // move robot if commands are sent
      // turning direction commands are triggers, and stay in place until a new servo direction is set. 
      // Forward and reverse directions are only activated if continually recieved.
      String command = messages[received];
      if(command == "FORWARD"){ // forward
        forward();
      }else if (command == "LEFT"){ // turning direction -> left
        turnLeft();
      }else if (command == "RIGHT"){ // turning direction -> right
        turnRight();
      }else if (command == "BACK"){ // reverse
        back();
      }else if(command == "GRAB"){
        openClaw();        
      }else if(command == "RELEASE"){
        closeClaw();
      }
      // print recieved message/command
      Serial.println(command);
    }else if(received == 1000){
      // blank command received
      Serial.println("NONE");
      // set speed to 0 when no forward or reverse command is received
      stop();
      digitalWrite(ledPin,HIGH);
    }else{
      // error in receiving
      Serial.println("ERROR");
      Serial.println(received);
    }
  }

  //Serial input commands
  if (Serial.available()) {
    char c = toupper(Serial.read());
    // Clear Serial Monitor
    if (c == 'C') {
      Serial.println(F("Clearing\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"));
    }else if (c == 'F') {
      forward();
    }else if (c == 'B') {
      back();
    }else if (c == 'L') {
      turnLeft();
    }else if (c == 'R') {
      turnRight();
    }else if (c == 'S') {
      stop();
    }else if (c == 'G'){
      openClaw();
    }
  }

}

void turnLeft(){
  left.write(leftForwardVal);
  right.write(rightBackVal);
}

void turnRight(){
  left.write(leftBackVal);
  right.write(rightForwardVal);
}

void back(){
  left.write(leftBackVal);
  right.write(rightBackVal);
}

void forward(){
  left.write(leftForwardVal);
  right.write(rightForwardVal);
}

void stop(){
  left.write(leftStopValue);
  right.write(rightStopValue);
}

void openClaw(){
  claw.write(clawOpenVal);
}

void closeClaw(){
  claw.write(clawCloseVal);
}

