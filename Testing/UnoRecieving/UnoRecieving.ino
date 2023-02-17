#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  lcd.begin(16, 2);

  Serial1.begin(9600);       // initialize UART with baud rate of 9600 bps
  pinMode(13,OUTPUT);
  Serial.begin(9600);

  String testing = "Initing..";
  lcd.print(testing);    
}

void loop() {
  lcd.setCursor(0, 1);
  if (Serial1.available()) {
    char data_rcvd = Serial1.read();   // read one byte from serial buffer and save to data_rcvd
    Serial.println(data_rcvd);
    if(data_rcvd=='0'){
    lcd.print("GRAB");
    }else{
      lcd.print("FORWARD");
    }
  }

}