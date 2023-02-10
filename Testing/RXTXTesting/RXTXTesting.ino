void setup() {
  // put your setup code here, to run once:
  Serial1.begin(9600);
  Serial.begin(9600);
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial1.available()){
    String val = Serial1.readString();
    Serial.println(val);
  }
}
