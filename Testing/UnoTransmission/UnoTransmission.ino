  int messageIndex = 0;

void setup() {
  Serial.begin(9600);       // initialize UART with baud rate of 9600 bps
}

void loop() {

  if(messageIndex == 0){
    messageIndex = 1;
  }else {
    messageIndex = 0;
  }

  char b[2];

  String str;

  str=String(messageIndex);

  str.toCharArray(b,2);

  Serial.write(b);
  delay(1000);

}