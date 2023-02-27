#include <LiquidCrystal.h>

//LCD setup
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// message index
const int messageLength = 6;
const String messages[messageLength] = {
  "GRAB   ",
  "FORWARD",
  "LEFT   ",
  "RIGHT  ",
  "BACK   ",
  "CENTER "
};
String command = "";

void setup() {
  //start LCD display
  lcd.begin(16, 2);

  Serial1.begin(9600);       // initialize UART with baud rate of 9600 bps
  Serial.begin(9600); // Initialize connection with computer

  String testing = "Initing.."; //test LCD
  lcd.print(testing);    
  delay(1000);
}

void loop() {
  lcd.clear();
  lcd.setCursor(0, 1);
  if (Serial1.available()) {
    char data_in = Serial1.read();   // read one byte from serial buffer and save to data_in
    Serial.println(data_in);

    int received = data_in - '0'; // convert recieved character to integer

    if (received >= 0 && received <= 999){
      command = messages[received];
      lcd.print(command);
      // print recieved message/command
      Serial.println(command);
    }else if(received == 1000){
      // blank command received
      lcd.print("NONE   ");
      Serial.println("NONE");
      // set speed to 0 when no forward or reverse command is received
    }else{
      // error in receiving
      lcd.print("ERROR    ");
      Serial.println("ERROR");
      Serial.println(received);
    }
    
  }else{
    Serial.println("broken");
  }

}