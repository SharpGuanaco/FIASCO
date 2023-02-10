#include <Wire.h>

// Set up a new SoftwareSerial object with RX in digital pin 10 and TX in digital pin 11
void setup() {
    // Set the baud rate for the SerialSoftware object
    //mySerial.begin(9600);
      Wire.begin(); 
}

int i = 0;
void loop() {
    // Send a byte with the value 45
    i++;
}