#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
int thumbDetector = 4;
int pointerDetector = 3;
int middleDetector = 2;
int ringDetector = 5;
int pinkyDetector = 6;
RF24 radio(7, 8); // CE, CSN
const byte address[6] = "00001";
//Thumb, Pointer, Middle, Ring, Pinky
const int numMessages = 6;
const bool checks[numMessages][5] = {
  {true,true,true,true,true},
  {true,true,false,true,true},
  {false,false,true,true,true},
  {false,true,true,true,true},
  {true,false,false,true,true},
  {true,false,false,false,false}
};
// related Strings
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
  const int messageIndex = checkTriggered();
  radio.write(&messageIndex, sizeof(int));
  delay(1000);
}


int checkTriggered(){
  String message = "None";
  int messageIndex = -1;
  bool triggered[5] = {digitalRead(thumbDetector),digitalRead(pointerDetector),digitalRead(middleDetector),digitalRead(ringDetector),digitalRead(pinkyDetector)};
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
  Serial.println(message);
  return messageIndex;
}
