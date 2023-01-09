#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
int detectorPin = 4;
RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();
  pinMode(detectorPin,INPUT);
  Serial.begin(9600);
}

unsigned long i = 0;
void loop() {
  i = i+1;
  if (digitalRead(detectorPin) == LOW){
    Serial.println(i);
    radio.write(&i, sizeof(unsigned long));
    delay(1000);
  }
}