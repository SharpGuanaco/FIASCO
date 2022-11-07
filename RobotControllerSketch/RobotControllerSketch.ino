//2023 FIASCO Robot Controller Sketch
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN
//ESC controller pins
int leftESC = 3;
int rightESC = 4;

const byte address[6] = "00001";

//list of commands, to help translate recieved indexes
//update both length and values as necessary
const int messageLength = 6;
const String messages[messageLength] = {
  "GRAB",
  "FORWARD",
  "LEFT",
  "RIGHT",
  "BACK",
  "TEST"
};

void setup() {
  //initialize serial
  Serial.begin(9600);
  //radio setup
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  //initialize output pins
  pinMode(leftESC, OUTPUT);
  pinMode(rightESC, OUTPUT);
}

void loop() {
  //read radio to see if messages are sent
  if (radio.available()) {
    char text[32] = "";
    int received = -2;
    radio.read(&received, sizeof(int));
    if (received >= 0){
      Serial.println(messages[received]);
    }else{
      Serial.println(received);
    }
  }

  //Serial input commands
  if (Serial.available()) {
    char c = toupper(Serial.read());
    if (c == 'C') {
      Serial.println(F("Clearing\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"));
      
    }
  }

}