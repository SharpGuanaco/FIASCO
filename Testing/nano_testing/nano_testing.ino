#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "printf.h"


RF24 radio(7, 8); // CE, CSN

const byte address[6] = "00001";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(10000);
  Serial.println("test1");
  Serial.println(radio.begin());

  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setAutoAck(true);
  radio.startListening();
}
int i = 0;
void loop() {
  // put your main code here, to run repeatedly:
  //delay(1000);
  //Serial.println("test");
}
