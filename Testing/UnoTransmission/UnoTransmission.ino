void setup() {
  Serial.begin(9600);       // initialize UART with baud rate of 9600 bps
}

void loop() {
  Serial.write('0');    // send the char '0' to serial if button is not pressed.
  delay(1000);
  Serial.write('1');                           // send the char '1' to serial if button is pressed.
  delay(1000);

}