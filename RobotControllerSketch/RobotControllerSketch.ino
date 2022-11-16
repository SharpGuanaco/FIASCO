//2023 FIASCO Robot Controller Sketch
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>


RF24 radio(7, 8); // CE, CSN
//ESC controller pins
Servo ESC;
Servo direction;

int left = 70;
int center = 100;
int right = 110;

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
  ESC.attach(5); 
  direction.attach(6);
}

void loop() {
  //read radio to see if messages are sent
  if (radio.available()) {
    unsigned long received = 1000;
    radio.read(&received, sizeof(unsigned long));
    if (received >= 0 && received <= 999){
      if(received == 1){
        ESC.writeMicroseconds(1565);
      }else if (received == 0){
        direction.write(center);
      }else if (received == 2){
        direction.write(left);

      }else if (received == 3){
        direction.write(right);
      }else if (received == 4){
        ESC.writeMicroseconds(1400);
      }
      Serial.println(messages[received]);
    }else if(received == 1000){
      Serial.println("None");
      ESC.writeMicroseconds(1500);
    }else{
      Serial.println("error");
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