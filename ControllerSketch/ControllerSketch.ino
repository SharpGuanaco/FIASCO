//2023 FIASCO Finger Controller Sketch
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
//finger detection pins
int thumbDetector = 2;
int pointerDetector = 3;
int middleDetector = 4;
int ringDetector = 5;
int pinkyDetector = 6;
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
//Thumb, Pointer, Middle, Ring, Pinky
//To add commands, increment the number below to the corresponding amount
const int numMessages = 6;
//next add the wanted trigger to the end of the array, in {thumb,pointer,middle,ring,pinky} format. 
//True means the finger is contracted while false means the finger is extended
const bool checks[numMessages][5] = {
  {true,true,true,true,true},
  {true,true,false,true,true},
  {false,false,true,true,true},
  {false,true,true,true,true},
  {true,false,false,true,true},
  {true,false,false,false,false}
};
//related Strings, add the wanted command to the end of the list
//not actually transmitted, but useful for troubleshooting. The other arduino converts the index of the list to the necessary message.
// Make sure to copy over to other sketch
const String messages[numMessages] = {
  "GRAB",
  "FORWARD",
  "LEFT",
  "RIGHT",
  "BACK",
  "TEST"
};


void setup() {
  //radio setup
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  //initialize detectors
  pinMode(thumbDetector,INPUT);
  pinMode(pointerDetector,INPUT);
  pinMode(middleDetector,INPUT);
  pinMode(ringDetector,INPUT);
  pinMode(pinkyDetector,INPUT);
  //initialize Serial interface
  Serial.begin(9600);
}

void loop() {
  //check for changes in finger positions
  unsigned long messageIndex = checkTriggered();
  Serial.println(messageIndex);
  //send updates to robot controller arduino
  radio.write(&messageIndex, sizeof(unsigned long));
  //delay to allow for finger movements, adjust as needed
  delay(1000);
}


int checkTriggered(){
  String message = "None";
  int messageIndex = 1000;
  //create array of all finger positions
  bool triggered[5] = {digitalRead(thumbDetector),digitalRead(pointerDetector),digitalRead(middleDetector),digitalRead(ringDetector),digitalRead(pinkyDetector)};
  //check to see if array matches any known configurations
  for(int i = 0; i < numMessages; i++){
    bool check = true;
    for (int j = 0; j<5;j++){
      if (triggered[j] != checks[i][j]){
        check = false;
      }
    }
      if (check){
        message = messages[i];
        messageIndex = i;
      }
  }
  //print out the message to be sent, and return index to be written to radio
  Serial.println(message);
  return messageIndex;
}
