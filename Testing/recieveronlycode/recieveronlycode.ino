#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "printf.h"

RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  Serial.begin(9600);
  Serial.println(F("test"));

  if(!radio.begin()){Serial.println("failed");}

  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setAutoAck(true);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    unsigned long input;
    radio.read(&input, sizeof(unsigned long));
    Serial.println(input);
  }

  if (Serial.available()) {
    char c = toupper(Serial.read());
    if (c == 'C') {
      Serial.println(F("Clearing\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"));
      
    }
  }

}