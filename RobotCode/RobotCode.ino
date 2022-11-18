//2023 FIASCO Robot Controller Sketch

//imports
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>

// radio setup
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";

//Robot Control Objects + Pins
Servo ESC;
Servo direction;

// Servo direction control constants
const int left = 70;
const int center = 97;
const int right = 110;

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
  radio.startListening();
  //initialize robot controller pins
  ESC.attach(5); 
  direction.attach(6);
  //set initial direction to center and intial speed to 0
  direction.write(center);
  ESC.writeMicroseconds(1500);
}


void loop() {
  //read radio to see if messages are sent
  if (radio.available()) {
    unsigned long received = 1000;
    radio.read(&received, sizeof(unsigned long));
    if (received >= 0 && received <= 999){
      // move robot if commands are sent
      // turning direction commands are triggers, and stay in place until a new servo direction is set. 
      // Forward and reverse directions are only activated if continually recieved.
      String command = messages[received];
      if(command == "FORWARD"){ // forward
        ESC.writeMicroseconds(1570);
      }else if (command == "CENTER"){ // turning direction -> center
        direction.write(center);
      }else if (command == "LEFT"){ // turning direction -> left
        direction.write(left);
      }else if (command == "RIGHT"){ // turning direction -> right
        direction.write(right);
      }else if (command == "BACK"){ // reverse
        ESC.writeMicroseconds(1400);
      }
      // print recieved message/command
      Serial.println(command);
    }else if(received == 1000){
      // blank command received
      Serial.println("NONE");
      // set speed to 0 when no forward or reverse command is received
      ESC.writeMicroseconds(1500);
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