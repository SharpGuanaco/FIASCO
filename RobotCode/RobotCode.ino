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

//Robot Control Objects + Pins
Servo left;
Servo right;

// Servo direction control constants
// const int left = 70;
// const int center = 97;
// const int right = 110;
const int rightStopValue = 95;
const int leftStopValue = 94;
const int leftForwardVal = 0;
const int rightForwardVal = 180;
const int leftBackVal = 180;
const int rightBackVal = 0;

//list of commands, to help translate recieved indexes
//update both length and values as necessary
const int messageLength = 6;
const String messages[messageLength] = {
  "GRAB",
  "FORWARD",
  "LEFT",
  "RIGHT",
  "BACK",
  "CENTER"
};


void setup() {
  //initialize serial
  Serial.begin(9600);
  //radio setup
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.setChannel(1);
  radio.startListening();
  radio.printDetails();

  //initialize robot controller pins
  left.attach(2); 
  right.attach(3);
  //set initial direction to center and intial speed to 0
  left.write(0);
  right.write(0);

  pinMode(5,OUTPUT);
}


void loop() {
  //read radio to see if messages are sent
  if (radio.available()) {
    unsigned long received = 1000;
    radio.read(&received, sizeof(unsigned long));
    if (received >= 0 && received <= 999){
      digitalWrite(5,LOW);
      // move robot if commands are sent
      // turning direction commands are triggers, and stay in place until a new servo direction is set. 
      // Forward and reverse directions are only activated if continually recieved.
      String command = messages[received];
      if(command == "FORWARD"){ // forward
        left.write(leftForwardVal);
        right.write(rightForwardVal);
      }else if (command == "LEFT"){ // turning direction -> left
        left.write(leftForwardVal);
        right.write(rightBackVal);
      }else if (command == "RIGHT"){ // turning direction -> right
        left.write(leftBackVal);
        right.write(rightForwardVal);
      }else if (command == "BACK"){ // reverse
        left.write(leftBackVal);
        right.write(rightBackVal);
      }
      // print recieved message/command
      Serial.println(command);
    }else if(received == 1000){
      // blank command received
      Serial.println("NONE");
      // set speed to 0 when no forward or reverse command is received
      left.write(leftStopValue);
      right.write(rightStopValue);
      digitalWrite(5,HIGH);
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
    }
  }
}